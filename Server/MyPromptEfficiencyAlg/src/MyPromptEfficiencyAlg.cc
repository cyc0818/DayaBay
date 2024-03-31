/**
 * MyPromptEfficiencyAlg
 *
 * Apr. 28, 2010  Created by ...
 */
#include "MyPromptEfficiencyAlg.h"

#include "Context/Context.h"
#include "Conventions/Detectors.h"
#include "Conventions/Electronics.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "DataSvc/ICableSvc.h"
#include "DetHelpers/ICoordSysSvc.h"
#include "Event/ReadoutHeader.h"
#include "Event/Readout.h"
#include "Event/ReadoutPmtCrate.h"
#include "Event/ReadoutPmtChannel.h"
#include "Event/SimReadoutHeader.h"
#include "Event/ElecHeader.h"
#include "Event/SimHeader.h"
#include "Event/SimHitHeader.h"
#include "Event/SimHitCollection.h"
#include "Event/GenHeader.h"
#include "Event/UserDataHeader.h"
#include "Event/RegistrationSequence.h"
#include "GaudiKernel/ITHistSvc.h"
#include "GaudiKernel/SystemOfUnits.h"
#include "HepMC/GenEvent.h"
#include "StatisticsSvc/IStatisticsSvc.h"
#include <vector>
#include "TVector3.h"
using namespace std;
using namespace DayaBay;


MyPromptEfficiencyAlg::MyPromptEfficiencyAlg(const std::string& name, ISvcLocator* pSvcLocator)
    :   GaudiAlgorithm(name, pSvcLocator),
        m_statsSvc(0),
        m_tree(0),
        m_ibd_tree(0),
        m_ncap_tree(0)
{
}

MyPromptEfficiencyAlg::~MyPromptEfficiencyAlg()
{
}

StatusCode MyPromptEfficiencyAlg::initialize()
{  
    //In origin algorithm template,
    //these two lines below are not cancelled,
    //but in the example I found,
    //these two lines do not exist. By Po-An
  //StatusCode sc;
  //sc = this->GaudiAlgorithm::initialize();

  // Initialize the necessary services

    int interest_ele[3] = {1,6,64};
    executionIndex = 0;
    for(int index = 0; index<MAXMCHISTS; index++){
        N_gen[index] = 0;
        N_double[index] = 0;


        for(int ele = 0; ele<3; ele++){
           N_gen_map[index].insert(pair<int,int>(interest_ele[ele],0));
        }
    }
    for(int index = 0; index<6; index++){
        N_lastsct[index] = 0;
        N_cap[index] = 0;
    }

    StatusCode sc = this->service("StatisticsSvc",m_statsSvc,true);
    if(sc.isFailure()){
      error() << "Failed to get StatisticsSvc" << endreq;
      return sc;
    }
    m_tree = new TTree("IBD_eff","efficiency tree");
    m_statsSvc->put("/file1/tree/IBD_eff",m_tree);
    m_ibd_tree = new TTree("IBD","Tree with Basic IBD parameters");
    m_statsSvc->put("/file1/tree/IBD",m_ibd_tree);
    m_ncap_tree = new TTree("nCapture","Neutron information in simulation stage (with or w/o trigger)");
    m_statsSvc->put("/file1/tree/nCapture",m_ncap_tree);


    string material_name[5] = {"db-gds1","db-iav1","db-lso1","db-oav1","db-oil1"};
    m_de.push_back(nullptr);
    for(int i = 0; i<5; i++){
        m_de.push_back(getDet<IDetectorElement>("/dd/Structure/AD/" + material_name[i]));
    }
    m_dbOil1 = m_de.at(5);



    return sc;
}

StatusCode MyPromptEfficiencyAlg::execute()
{
  info() << "MyPromptEfficiencyAlg executing ... " << executionIndex << endreq;

  DayaBay::UserDataHeader* calibs = get<DayaBay::UserDataHeader>("/Event/Data/CalibStats");
  if(!calibs){
      error() << "Failed to get calibstats header." << endreq;
      return StatusCode::FAILURE;
  }

  DayaBay::RecHeader* recHeader = get<DayaBay::RecHeader>("/Event/Rec/AdSimple");
  if(!recHeader){
      error() << "Failed to get readout header." << endreq;
      return StatusCode::FAILURE;
  }else{
      //info() << (*recHeader) << endreq;
  }
  DayaBay::RecTrigger recTrigger = recHeader->recTrigger();
  //info() << "Reconstruncted energy = " << recTrigger.energy() << endreq;
  //info() << "Reconstructed x = " << recTrigger.position().x() << endreq;
  info() << "Reconstructed t = " << recTrigger.triggerTime() << endreq;
  info() << "Reconstructed sec = " << recTrigger.triggerTime().GetSeconds() << endreq;
  info() << "Reconstructed nano_sec = " << recTrigger.triggerTime().GetNanoSec() << endreq;
  processGenHeader();
    //I want to start from ReadoutHeader to track that how many Prompt(e+) generated event successfully turn into readout.
  DayaBay::ReadoutHeader* readoutHeader = 
    get<DayaBay::ReadoutHeader>("/Event/Readout/ReadoutHeader");
  if(!readoutHeader){
    error() << "Failed to get readout header." << endreq;
    return StatusCode::FAILURE;
  }
  const DayaBay::DaqCrate* readout = readoutHeader->daqCrate();
  if(!readout){
    error() << "Failed to get readout from header" << endreq;
    return StatusCode::FAILURE;
  }
  int runNumber = readout->runNumber();
  run_Number = runNumber;
  //info() << "RunNumber = " << runNumber << endreq;
    //info() << "Readout Name = " << (*readoutHeader) << endreq;
    vector<const IHeader*> inputHeaders = readoutHeader->inputHeaders();
    vector<const IHeader*>::const_iterator headerIter_inputHeaders, 
      headerIterEnd_inputHeaders = inputHeaders.end();

    const SimReadoutHeader* simReadoutHeader = 0;
    for(headerIter_inputHeaders = inputHeaders.begin();
            headerIter_inputHeaders!=headerIterEnd_inputHeaders;
            headerIter_inputHeaders++)
    {
        simReadoutHeader = dynamic_cast<const SimReadoutHeader*>(*headerIter_inputHeaders);
        if(simReadoutHeader){
            //info() << "Found SimReadoutHeader" << endreq;
            //info() << "SimReadout Name = " << (*simReaoutHeader) << endreq;
	        break;
        }else{
            //info() << "SimReadoutHeader Not Found" << endreq;
        }
    }

    const ElecHeader* elecHeader = 0;
    if(simReadoutHeader){
        inputHeaders = simReadoutHeader->inputHeaders();
        headerIterEnd_inputHeaders = inputHeaders.end();
        for(headerIter_inputHeaders = inputHeaders.begin();
                headerIter_inputHeaders!=headerIterEnd_inputHeaders;
                headerIter_inputHeaders++)
        {
            elecHeader = dynamic_cast<const ElecHeader*>(*headerIter_inputHeaders);
            if(elecHeader){
                //info() << "Found ElecHeader" << endreq;
                break;
            }else{
                //info() << "ElecHeader Not Found" << endreq;
            }

        }
    }

    const SimHeader* simHeader = 0;
    if(elecHeader){
        inputHeaders = elecHeader->inputHeaders();
        headerIterEnd_inputHeaders = inputHeaders.end();
        for(headerIter_inputHeaders = inputHeaders.begin();
                headerIter_inputHeaders!=headerIterEnd_inputHeaders;
                headerIter_inputHeaders++)
        {
            simHeader = dynamic_cast<const SimHeader*>(*headerIter_inputHeaders);
            if(simHeader){
                //TH1I* simtimes = dynamic_cast<TH1I*>(this->getOrMakeHist(runNumber,SIMREADTIMES));
                //simtimes->Fill(simHeader->execNumber());
                //info() << "Found SimHeader" << endreq;
                //info() << "Sim Name = " << (*simHeader) << endreq;
                break;
            }else{
                //info() << "SimHeader Not Found" << endreq;
            }
        }
    }

    const GenHeader* genHeader = 0;
    std::map<int, IBDpair*>::iterator IBDIter;
    if(simHeader){
        inputHeaders = simHeader->inputHeaders();
        headerIterEnd_inputHeaders = inputHeaders.end();
        for(headerIter_inputHeaders = inputHeaders.begin();
                headerIter_inputHeaders!=headerIterEnd_inputHeaders;
                headerIter_inputHeaders++){
            genHeader = dynamic_cast<const GenHeader*>(*headerIter_inputHeaders);
            if(genHeader){
                //TH1I* gentimes = dynamic_cast<TH1I*>(getOrMakeHist(runNumber,GENREADTIMES));
                //gentimes->Fill(genHeader->execNumber());
                //info() << "Gen Name = " << (genHeader->generatorName()) << endreq;
                TH1I* simtimes = dynamic_cast<TH1I*>(this->getOrMakeHist(runNumber,judgeGeneratorName(genHeader->generatorName())));
                simtimes->Fill(simHeader->execNumber());               
                IBDIter = IBDmap.find(simHeader->execNumber());
                if(IBDIter==IBDmap.end()){
                    struct IBDpair* ibd = new IBDpair();
                    (ibd->ready) = false;
                    (ibd->isPromptFlasher) = isFlasher(calibs, recTrigger);
                    IBDmap[simHeader->execNumber()] = ibd;    
                    fillIBDstruct(ibd, judgeGeneratorName(genHeader->generatorName()), recTrigger);
                }else{
                    struct IBDpair* ibd = IBDIter->second;
                    if(ibd->ready == false){
                        (ibd->ready) = true;
                        (ibd->isDelayFlasher) = isFlasher(calibs, recTrigger);
                        fillIBDstruct(ibd, 0, recTrigger);
                        fillIBDunobservableStatistics(ibd, simHeader);
                    }else if(ibd->ready == true){
                        (ibd->isThirdFlasher) = isFlasher(calibs, recTrigger);
                        (ibd->e3) = recTrigger.energy();
                        (ibd->x3) = recTrigger.position().x();
                        (ibd->y3) = recTrigger.position().y();
                        (ibd->z3) = recTrigger.position().z();
                        (ibd->t3) = ((long long)recTrigger.triggerTime().GetSeconds())*1000000000+recTrigger.triggerTime().GetNanoSec();
                    }
                }
                break;
            }else{
                //info() << "GenHeader Not Found" << endreq;
            }
        }
    }

    executionIndex++;
  return StatusCode::SUCCESS;
}

StatusCode MyPromptEfficiencyAlg::finalize()
{
  StatusCode sc;
  //sc = this->GaudiAlgorithm::finalize();
  fillFinalTree(run_Number);
  fillIBDTree();
  std::map<int,TH1**>::iterator histIter, histEnd = m_shortCuts.end();
  for(histIter = m_shortCuts.begin(); histIter!=histEnd; histIter++){
    delete [] (histIter->second);
    histIter->second = 0;
  }
  std::map<int, IBDpair*>::iterator IBDmapIter, IBDmapIterEnd = IBDmap.end();
  for(IBDmapIter = IBDmap.begin(); IBDmapIter!=IBDmapIterEnd; IBDmapIter++){
      delete IBDmapIter->second;
      IBDmapIter->second = 0;
  }
  //delete m_tree;
  if( m_statsSvc ) m_statsSvc->release();
  for(int index = 0; index<MAXMCHISTS; index++){
      info() << "IBDcode = " << index << "," << N_gen[index] << "," << N_double[index] << endreq;
  }

  return StatusCode::SUCCESS;
}

TH1* MyPromptEfficiencyAlg::getOrMakeHist(int run, int histCode){
    map<int, TH1**>::iterator histIter = m_shortCuts.find(run);
    TH1** histograms = 0;
    if( histIter == m_shortCuts.end() ){
        histograms = new TH1*[MAXMCHISTS];
        for(int i = 0; i<MAXMCHISTS; i++) histograms[i] = 0;
        m_shortCuts[run] = histograms;
    }else{
        histograms = histIter->second;
    }
    TH1* h = histograms[histCode];
    string histName;
    if(!h){
        //Make histogram
        switch(histCode){
            case SIMREADTIMES_oil:
                histName = "SimReadoutTimes_oil";
                h = new TH1I(histName.c_str(),
                        "times a Sim IBD_oil become readout",
                        4800,
                        0,
                        4800);
                h->GetXaxis()->SetTitle("No.Sim");
                h->GetYaxis()->SetTitle("Times");
                break;
            case SIMREADTIMES_lso:
                histName = "SimReadoutTimes_lso";
                h = new TH1I(histName.c_str(),
                        "times a Sim IBD_lso turning to readout",
                        4800,
                        0,
                        4800);
                h->GetXaxis()->SetTitle("No.Sim");
                h->GetYaxis()->SetTitle("Times");
                break;
            case SIMREADTIMES_gds:
                histName = "SimReadoutTimes_gds";
                h = new TH1I(histName.c_str(),
                        "times a Sim IBD_gds turning to readout",
                        4800,
                        0,
                        4800);
                h->GetXaxis()->SetTitle("No.Sim");
                h->GetYaxis()->SetTitle("Times");
                break;
            case SIMREADTIMES_acrylic:
                histName = "SimReadoutTimes_acrylic";
                h = new TH1I(histName.c_str(),
                        "times a Sim IBD_acrylic turning to readout",
                        4800,
                        0,
                        4800);
                h->GetXaxis()->SetTitle("No.Sim");
                h->GetYaxis()->SetTitle("Times");
                break;
            case SIMREADTIMES_fullvol:
                histName = "SimReadoutTimes_fullvol";
                h = new TH1I(histName.c_str(),
                        "times a Sim IBD_fullvol turning to readout",
                        4800,
                        0,
                        4800);
                h->GetXaxis()->SetTitle("No.Sim");
                h->GetYaxis()->SetTitle("Times");
                break;
            default:
                error() << "Unknowing histograms code = " << histCode << endreq;
                return 0;
        }
        debug() << "Making histogram: " << histName << endreq;
        //m_statsSvc->put( this->getPath(run, histName.c_str()), h);
        histograms[histCode] = h;
    }
    return h;
}

string MyPromptEfficiencyAlg::getPath(int run, const char* histName){
  // Construct histogram path in statistics service
  stringstream path;
  path << "/file1/mctruth/source_ibd/" << histName;
  return path.str();
}
//string MyPromptEfficiencyAlg::getPath(int run, const char* histName){
//  // Construct histogram path in statistics service
//  stringstream path;
//  path << "/file1/run_" << std::setfill('0') << std::setw(7) 
//       << run;
//  path << "/mctruth/source_ibd/" << histName;
//  return path.str();
//}

int MyPromptEfficiencyAlg::judgeGeneratorName(const string& generatorName){
    /*if(generatorName=="IBD_DYB_AD1_oil") return SIMREADTIMES_oil;
    else if(generatorName=="IBD_DYB_AD1_LS") return SIMREADTIMES_lso;
    else if(generatorName=="IBD_DYB_AD1_GdLS") return SIMREADTIMES_gds;
    else if(generatorName=="IBD_DYB_AD1_acrylic") return SIMREADTIMES_acrylic;*/


    if(generatorName=="IBD_oil") return SIMREADTIMES_oil;
    else if(generatorName=="IBD_lso") return SIMREADTIMES_lso;
    else if(generatorName=="IBD_gds") return SIMREADTIMES_gds;
    else if(generatorName=="IBD_acrylic") return SIMREADTIMES_acrylic;
    else if(generatorName=="IBD_DYB_AD1_GdLS") return SIMREADTIMES_fullvol;

}

StatusCode MyPromptEfficiencyAlg::processGenHeader(){
  const DayaBay::GenHeader *genHdr = 0;
  const DayaBay::SimHeader *simHdr = 0;

  std::vector<const DayaBay::IHeader*> req_headers;
  std::vector<const DayaBay::IHeader*>::const_iterator header_itr;

  const DayaBay::RegistrationSequence *regseq = get<DayaBay::RegistrationSequence>
    (DayaBay::RegistrationSequence::defaultLocation() );

  const DayaBay::RegistrationSequence::Registrations& reglist = regseq->registrations();
  DayaBay::RegistrationSequence::Registrations::const_iterator regIt, regend = reglist.end();

  for (regIt=reglist.begin(); regIt!=regend; regIt++) {
    const DataObject *objreg = (*regIt).object();
    
    if (objreg->clID() == DayaBay::SimHeader::classID()) {
      simHdr = dynamic_cast<const DayaBay::SimHeader*>(objreg);


      /* 2022 Feb.23 added */
      int this_element = 0;
      int this_element_mass = 0;
      const SimUnobservableStatisticsHeader* unob = simHdr->unobservableStatistics();
      const SimUnobservableStatisticsHeader::stat_map& unmap = unob->stats();
      SimUnobservableStatisticsHeader::stat_map::const_iterator unobIter, unobIterEnd = unmap.end();
      for(unobIter = unmap.begin(); unobIter!=unobIterEnd; unobIter++){
          if(unobIter->first == "capTarget") this_element = unobIter->second.sum();
          if(unobIter->first == "capTargetMass") this_element_mass = unobIter->second.sum();
          //if(unobIter->first == "capTarget_Trk2") this_element = unobIter->second.sum();
      }
      info() << "CapTarget = " << this_element << endreq;
      info() << "CapTargetMass = " << this_element_mass << endreq;

      req_headers = simHdr->inputHeaders();
      //info() << "Size of siminputHeaders = " << req_headers.size() << endreq;
      if (req_headers.size()==0) warning() << "No related genHeaders found." << endreq;

      for (header_itr=req_headers.begin(); header_itr!=req_headers.end(); ++header_itr) {
        genHdr = dynamic_cast<const DayaBay::GenHeader*> (*header_itr);
        int IBDcode = judgeGeneratorName(genHdr->generatorName());
        //info() << "IBDcode = " << IBDcode << endreq;
        N_gen[IBDcode]++;
        N_gen_map[IBDcode][this_element]++;
      }


      /* 2022 Jul.19 update */
        const DayaBay::SimParticleHistory* pHist = simHdr->particleHistory();
        if(!pHist) continue;
        const list<DayaBay::SimTrack*> trk=pHist->tracks();
        for(list<DayaBay::SimTrack*>::const_iterator itr = trk.begin(); itr!=trk.end(); itr++){
        
            if((*itr)->particle() != 2112) continue;
            const vector<SimVertex*> ptclVtx = (*itr)->vertices();


            vector<SimVertex*>::const_iterator gen_vtx = ptclVtx.begin();   // IBD vertex
            vector<SimVertex*>::const_iterator bfc_vtx = ptclVtx.end()-2;   // before neutron capture (last scattering)
            vector<SimVertex*>::const_iterator cap_vtx = ptclVtx.end()-1;   // neutron capture
            if(ptclVtx.size() < 2){
                bfc_vtx = gen_vtx;
                cap_vtx = gen_vtx;
                info() << "No scattering before captured" << endreq;
            }



            const Gaudi::XYZPoint glb_Gen = (*gen_vtx)->position();
            Gaudi::XYZPoint lcl_Gen = m_dbOil1->geometry()->toLocal(glb_Gen);
            int vol_index_gen = 0;
            for(int i = 1; i<m_de.size(); i++){
                if(m_de.at(i)->geometry()->isInside(glb_Gen)) vol_index_gen = i;
                if(vol_index_gen) break;
            }
            N_lastsct[vol_index_gen]++;
            info() << "GeneratingVolume = " << vol_index_gen << endreq;
            info() << "x = " << lcl_Gen.x() << " , y = " << lcl_Gen.y() << " , z = " << lcl_Gen.z() << endreq;


            const Gaudi::XYZPoint glb_LastSct = (*bfc_vtx)->position();
            Gaudi::XYZPoint lcl_LastSct = m_dbOil1->geometry()->toLocal(glb_LastSct);
            int vol_index_sct = 0;
            for(int i = 1; i<m_de.size(); i++){
                if(m_de.at(i)->geometry()->isInside(glb_LastSct)) vol_index_sct = i;
                if(vol_index_sct) break;
            }
            N_lastsct[vol_index_sct]++;
            info() << "LastScatterVolume = " << vol_index_sct << endreq;
            info() << "x = " << lcl_LastSct.x() << " , y = " << lcl_LastSct.y() << " , z = " << lcl_LastSct.z() << endreq;


            const Gaudi::XYZPoint glb_Cap = (*cap_vtx)->position();
            Gaudi::XYZPoint lcl_Cap = m_dbOil1->geometry()->toLocal(glb_Cap);
            int vol_index_cap = 0;
            for(int i = 1; i<m_de.size(); i++){
                if(m_de.at(i)->geometry()->isInside(glb_Cap)) vol_index_cap = i;
                if(vol_index_cap) break;
            }
            N_cap[vol_index_cap]++;
            info() << "CapturedVolume = " << vol_index_cap << endreq;
            info() << "x = " << lcl_Cap.x() << " , y = " << lcl_Cap.y() << " , z = " << lcl_Cap.z() << endreq;


            nCapture temp;
            temp.vol_gen = vol_index_gen;
            temp.vtx_gen.SetXYZ(lcl_Gen.x(),lcl_Gen.y(),lcl_Gen.z());
            temp.KE_gen = (*gen_vtx)->kineticEnergy();

            temp.vol_sct = vol_index_sct;
            temp.vtx_sct.SetXYZ(lcl_LastSct.x(),lcl_LastSct.y(),lcl_LastSct.z());
            temp.KE_bfcap = (*bfc_vtx)->kineticEnergy();

            temp.vol_cap = vol_index_cap;
            temp.vtx_cap.SetXYZ(lcl_Cap.x(),lcl_Cap.y(),lcl_Cap.z());
            temp.KE_cap = (*cap_vtx)->kineticEnergy();

            temp.CapTarget = this_element;
            temp.CapTargetMass = this_element_mass;
            nCapV.push_back(temp);


        }

    }   
  }
    return StatusCode::SUCCESS;
}

StatusCode MyPromptEfficiencyAlg::fillFinalTree(int run){
    map<int, TH1**>::iterator histIter = m_shortCuts.find(run);
    TH1** histograms = 0;
    histograms = histIter->second;
    for(int no = 0; no<4800; no++){
        for(int IBDcode = 0; IBDcode < MAXMCHISTS; IBDcode++){
            TH1I* h = dynamic_cast<TH1I*>(histograms[IBDcode]);
            if(!h) continue;
            if(h->GetBinContent(no)>=2){
                N_double[IBDcode]++;
            }
        }
    }
    int N_gen_oil,N_gen_lso,N_gen_gds,N_gen_acrylic,N_gen_fullvol;
    int N_gen_oil_H,N_gen_oil_Gd,N_gen_oil_C;
    int N_gen_lso_H,N_gen_lso_Gd,N_gen_lso_C;
    int N_gen_gds_H,N_gen_gds_Gd,N_gen_gds_C;
    int N_gen_acrylic_H,N_gen_acrylic_Gd,N_gen_acrylic_C;
    int N_gen_fullvol_H,N_gen_fullvol_Gd,N_gen_fullvol_C;
    int N_double_oil,N_double_lso,N_double_gds,N_double_acrylic,N_double_fullvol;

    /* 2022 Jul.19 update */
    int N_lastsct_GdLS,N_lastsct_IAV,N_lastsct_LS,N_lastsct_OAV,N_lastsct_MO;
    int N_cap_GdLS,N_cap_IAV,N_cap_LS,N_cap_OAV,N_cap_MO;

    m_tree->Branch("N_gen_oil",&N_gen_oil);
    m_tree->Branch("N_gen_lso",&N_gen_lso);
    m_tree->Branch("N_gen_gds",&N_gen_gds);
    m_tree->Branch("N_gen_acrylic",&N_gen_acrylic);
    m_tree->Branch("N_gen_fullvol",&N_gen_fullvol);

    m_tree->Branch("N_gen_oil_H",&N_gen_oil_H);
    m_tree->Branch("N_gen_lso_H",&N_gen_lso_H);
    m_tree->Branch("N_gen_gds_H",&N_gen_gds_H);
    m_tree->Branch("N_gen_acrylic_H",&N_gen_acrylic_H);
    m_tree->Branch("N_gen_fullvol_H",&N_gen_fullvol_H);

    m_tree->Branch("N_gen_oil_Gd",&N_gen_oil_Gd);
    m_tree->Branch("N_gen_lso_Gd",&N_gen_lso_Gd);
    m_tree->Branch("N_gen_gds_Gd",&N_gen_gds_Gd);
    m_tree->Branch("N_gen_acrylic_Gd",&N_gen_acrylic_Gd);
    m_tree->Branch("N_gen_fullvol_Gd",&N_gen_fullvol_Gd);

    m_tree->Branch("N_gen_oil_C",&N_gen_oil_C);
    m_tree->Branch("N_gen_lso_C",&N_gen_lso_C);
    m_tree->Branch("N_gen_gds_C",&N_gen_gds_C);
    m_tree->Branch("N_gen_acrylic_C",&N_gen_acrylic_C);
    m_tree->Branch("N_gen_fullvol_C",&N_gen_fullvol_C);

    m_tree->Branch("N_double_oil",&N_double_oil);
    m_tree->Branch("N_double_lso",&N_double_lso);
    m_tree->Branch("N_double_gds",&N_double_gds);
    m_tree->Branch("N_double_acrylic",&N_double_acrylic);
    m_tree->Branch("N_double_fullvol",&N_double_fullvol);

    /* 2022 Jul.19 update */
    m_tree->Branch("N_lastsct_GdLS",&N_lastsct_GdLS);
    m_tree->Branch("N_lastsct_IAV",&N_lastsct_IAV);
    m_tree->Branch("N_lastsct_LS",&N_lastsct_LS);
    m_tree->Branch("N_lastsct_OAV",&N_lastsct_OAV);
    m_tree->Branch("N_lastsct_MO",&N_lastsct_MO);

    m_tree->Branch("N_cap_GdLS",&N_cap_GdLS);
    m_tree->Branch("N_cap_IAV",&N_cap_IAV);
    m_tree->Branch("N_cap_LS",&N_cap_LS);
    m_tree->Branch("N_cap_OAV",&N_cap_OAV);
    m_tree->Branch("N_cap_MO",&N_cap_MO);

    N_gen_oil = N_gen[SIMREADTIMES_oil];
    N_gen_lso = N_gen[SIMREADTIMES_lso];
    N_gen_gds = N_gen[SIMREADTIMES_gds];
    N_gen_acrylic = N_gen[SIMREADTIMES_acrylic];
    N_gen_fullvol = N_gen[SIMREADTIMES_fullvol];

    N_gen_oil_H = N_gen_map[SIMREADTIMES_oil][1];
    N_gen_lso_H = N_gen_map[SIMREADTIMES_lso][1];
    N_gen_gds_H = N_gen_map[SIMREADTIMES_gds][1];
    N_gen_acrylic_H = N_gen_map[SIMREADTIMES_acrylic][1];
    N_gen_fullvol_H = N_gen_map[SIMREADTIMES_fullvol][1];

    N_gen_oil_Gd = N_gen_map[SIMREADTIMES_oil][64];
    N_gen_lso_Gd = N_gen_map[SIMREADTIMES_lso][64];
    N_gen_gds_Gd = N_gen_map[SIMREADTIMES_gds][64];
    N_gen_acrylic_Gd = N_gen_map[SIMREADTIMES_acrylic][64];
    N_gen_fullvol_Gd = N_gen_map[SIMREADTIMES_fullvol][64];

    N_gen_oil_C = N_gen_map[SIMREADTIMES_oil][6];
    N_gen_lso_C = N_gen_map[SIMREADTIMES_lso][6];
    N_gen_gds_C = N_gen_map[SIMREADTIMES_gds][6];
    N_gen_acrylic_C = N_gen_map[SIMREADTIMES_acrylic][6];
    N_gen_fullvol_C = N_gen_map[SIMREADTIMES_fullvol][6];

    N_double_oil = N_double[SIMREADTIMES_oil];
    N_double_lso = N_double[SIMREADTIMES_lso];
    N_double_gds = N_double[SIMREADTIMES_gds];
    N_double_acrylic = N_double[SIMREADTIMES_acrylic];
    N_double_fullvol = N_double[SIMREADTIMES_fullvol];

    /* 2022 Jul.19 update */
    N_lastsct_GdLS = N_lastsct[1];
    N_lastsct_IAV = N_lastsct[2];
    N_lastsct_LS = N_lastsct[3];
    N_lastsct_OAV = N_lastsct[4];
    N_lastsct_MO = N_lastsct[5];

    N_cap_GdLS = N_cap[1];
    N_cap_IAV = N_cap[2];
    N_cap_LS = N_cap[3];
    N_cap_OAV = N_cap[4];
    N_cap_MO = N_cap[5];

    m_tree->Fill();
    return StatusCode::SUCCESS;
}

StatusCode MyPromptEfficiencyAlg::fillIBDstruct(struct IBDpair* ibd, int IBDcode, DayaBay::RecTrigger& recTrigger){
    if(ibd->ready){
        (ibd->ed) = recTrigger.energy();
        (ibd->xd) = recTrigger.position().x();
        (ibd->yd) = recTrigger.position().y();
        (ibd->zd) = recTrigger.position().z();
        (ibd->td) = ((long long)recTrigger.triggerTime().GetSeconds())*1000000000+recTrigger.triggerTime().GetNanoSec();
        info() << "This is DELAY Time = " << (ibd->td) << endreq;
        info() << "Checking = " << (long long)recTrigger.triggerTime().GetSeconds()*1000000000 << endreq;
    }else{
        (ibd->genType) = IBDcode;
        (ibd->ep) = recTrigger.energy();
        (ibd->xp) = recTrigger.position().x();
        (ibd->yp) = recTrigger.position().y();
        (ibd->zp) = recTrigger.position().z();
        (ibd->tp) = ((long long)recTrigger.triggerTime().GetSeconds())*1000000000+recTrigger.triggerTime().GetNanoSec();
        info() << "This is PROMPT Time = " << (ibd->tp) << endreq;
        info() << "Checking = " << (long long)recTrigger.triggerTime().GetSeconds()*1000000000 << endreq;
    }
    return StatusCode::SUCCESS;
}

StatusCode MyPromptEfficiencyAlg::fillIBDTree(){
    int genType, capTarget, capVol, capTargetMass;
    double ep,xp,yp,zp,ed,xd,yd,zd,e3,x3,y3,z3,dist;
    double ept,xpt,ypt,zpt,xdt,ydt,zdt;
    long long dT,dT3;
    bool isPromptFlasher, isDelayFlasher, isThirdFlasher;
    double EDepInGdLS,EDepInLS,QEDepInGdLS,QEDepInLS,QuenchedEnergy,DepositedEnergy;
    double EDepInOIL,QEDepInOIL;
    m_ibd_tree->Branch("genType",           &genType);
    m_ibd_tree->Branch("capTarget",         &capTarget);
    m_ibd_tree->Branch("capTargetMass",         &capTargetMass);
    m_ibd_tree->Branch("capVol",            &capVol);
    m_ibd_tree->Branch("EDepInGdLS",        &EDepInGdLS);
    m_ibd_tree->Branch("EDepInLS",          &EDepInLS);
    m_ibd_tree->Branch("EDepInOIL",         &EDepInOIL);
    m_ibd_tree->Branch("QEDepInGdLS",       &QEDepInGdLS);
    m_ibd_tree->Branch("QEDepInLS",         &QEDepInLS);
    m_ibd_tree->Branch("QEDepInOIL",        &QEDepInOIL);
    m_ibd_tree->Branch("QuenchedEnergy",    &QuenchedEnergy);
    m_ibd_tree->Branch("DepositedEnergy",   &DepositedEnergy);
    m_ibd_tree->Branch("ep",&ep);
    m_ibd_tree->Branch("xp",&xp);
    m_ibd_tree->Branch("yp",&yp);
    m_ibd_tree->Branch("zp",&zp);
    m_ibd_tree->Branch("ed",&ed);
    m_ibd_tree->Branch("xd",&xd);
    m_ibd_tree->Branch("yd",&yd);
    m_ibd_tree->Branch("zd",&zd);
    m_ibd_tree->Branch("e3",&e3);
    m_ibd_tree->Branch("x3",&x3);
    m_ibd_tree->Branch("y3",&y3);
    m_ibd_tree->Branch("z3",&z3);
    m_ibd_tree->Branch("dT",&dT);
    m_ibd_tree->Branch("dT3",&dT3);
    m_ibd_tree->Branch("dist",&dist);
    m_ibd_tree->Branch("ept",&ept);
    m_ibd_tree->Branch("xpt",&xpt);
    m_ibd_tree->Branch("ypt",&ypt);
    m_ibd_tree->Branch("zpt",&zpt);
    m_ibd_tree->Branch("xdt",&xdt);
    m_ibd_tree->Branch("ydt",&ydt);
    m_ibd_tree->Branch("zdt",&zdt);
    m_ibd_tree->Branch("isPromptFlasher",&isPromptFlasher);
    m_ibd_tree->Branch("isDelayFlasher",&isDelayFlasher);
    m_ibd_tree->Branch("isThirdFlasher",&isThirdFlasher);
    std::map<int,IBDpair*>::iterator iter,iterEnd = IBDmap.end();
    for(iter = IBDmap.begin(); iter!=iterEnd; iter++){
        IBDpair* ibd = iter->second;
        if(ibd->ready){
            genType     = ibd->genType;
            capTarget   = ibd->capTarget;
            capTargetMass   = ibd->capTargetMass;
            capVol      = ibd->capVol;
            EDepInGdLS  = ibd->EDepInGdLS;
            EDepInLS    = ibd->EDepInLS;
            EDepInOIL   = ibd->EDepInOIL;
            QEDepInGdLS = ibd->QEDepInGdLS;
            QEDepInLS   = ibd->QEDepInLS;
            QEDepInOIL  = ibd->QEDepInOIL;
            QuenchedEnergy = QEDepInGdLS + QEDepInLS + QEDepInOIL;
            DepositedEnergy = EDepInGdLS + EDepInLS  + EDepInOIL;
            ep          = ibd->ep;
            xp          = ibd->xp;
            yp          = ibd->yp;
            zp          = ibd->zp;
            ed          = ibd->ed;
            xd          = ibd->xd;
            yd          = ibd->yd;
            zd          = ibd->zd;
            e3          = ibd->e3;
            x3          = ibd->x3;
            y3          = ibd->y3;
            z3          = ibd->z3;
            dT          = (ibd->td) - (ibd->tp);
            dT3         = (ibd->t3) - (ibd->td);
            dist        = sqrt(pow(xd-xp,2)+pow(yd-yp,2)+pow(zd-zp,2));
            ept         = ibd->ept;
            xpt         = ibd->xpt;
            ypt         = ibd->ypt;
            zpt         = ibd->zpt;
            xdt         = ibd->xdt;
            ydt         = ibd->ydt;
            zdt         = ibd->zdt;
            isPromptFlasher = ibd->isPromptFlasher;
            isDelayFlasher  = ibd->isDelayFlasher;
            isThirdFlasher  = ibd->isThirdFlasher;
            m_ibd_tree->Fill();
        }else{
            continue;
        }
    }

    /* 2022 Jul.19 update */
    int vol_gen, vol_sct, vol_cap;
    int CapTarget, CapTargetMass;
    double x_gen, y_gen, z_gen, KE_gen;
    double x_sct, y_sct, z_sct, KE_bfcap;
    double x_cap, y_cap, z_cap, KE_cap;
    m_ncap_tree->Branch("GenVol",&vol_gen);
    m_ncap_tree->Branch("LastScatterVol",&vol_sct);
    m_ncap_tree->Branch("CapVol",&vol_cap);
    m_ncap_tree->Branch("CapTarget",&CapTarget);
    m_ncap_tree->Branch("CapTargetMass",&CapTargetMass);
    m_ncap_tree->Branch("xgen",&x_gen);
    m_ncap_tree->Branch("ygen",&y_gen);
    m_ncap_tree->Branch("zgen",&z_gen);
    m_ncap_tree->Branch("KEgen",&KE_gen);
    m_ncap_tree->Branch("xsct",&x_sct);
    m_ncap_tree->Branch("ysct",&y_sct);
    m_ncap_tree->Branch("zsct",&z_sct);
    m_ncap_tree->Branch("KEbfcap",&KE_bfcap);
    m_ncap_tree->Branch("xcap",&x_cap);
    m_ncap_tree->Branch("ycap",&y_cap);
    m_ncap_tree->Branch("zcap",&z_cap);
    m_ncap_tree->Branch("KEcap",&KE_cap);

    for(vector<nCapture>::const_iterator it = nCapV.begin(); it!=nCapV.end(); it++){

        vol_gen = it->vol_gen;
        vol_sct = it->vol_sct;
        vol_cap = it->vol_cap;
        CapTarget = it->CapTarget;
        CapTargetMass = it->CapTargetMass;
        x_gen = it->vtx_gen.X();
        y_gen = it->vtx_gen.Y();
        z_gen = it->vtx_gen.Z();
        KE_gen = it->KE_gen;
        x_sct = it->vtx_sct.X();
        y_sct = it->vtx_sct.Y();
        z_sct = it->vtx_sct.Z();
        KE_bfcap = it->KE_bfcap;
        x_cap = it->vtx_cap.X();
        y_cap = it->vtx_cap.Y();
        z_cap = it->vtx_cap.Z();
        KE_cap = it->KE_cap;

        m_ncap_tree->Fill();
    }


    return StatusCode::SUCCESS;
}

bool MyPromptEfficiencyAlg::isFlasher(DayaBay::UserDataHeader* userData, const DayaBay::RecTrigger& recTrigger){
    float MaxQ = userData->getFloat("MaxQ");
    float Quadrant = userData->getFloat("Quadrant");
    float MaxQ_2inchPMT = userData->getFloat("MaxQ_2inchPMT");
    double e = recTrigger.energy();
    if( (MaxQ/0.45*MaxQ/0.45+Quadrant*Quadrant > 1) || (MaxQ_2inchPMT > 100 && e < 20.) )
        return true;
    else 
        return false;
}

StatusCode MyPromptEfficiencyAlg::fillIBDunobservableStatistics(struct IBDpair* ibd, const SimHeader* simHeader){
    const SimUnobservableStatisticsHeader* unobservable = simHeader->unobservableStatistics();
    if(!unobservable){
        warning() << "Unobservable Not Found!!" << endreq;
        return StatusCode::FAILURE;
    }


    TVector3 vtx_anni(0,0,0); 
    TVector3 vtx_cap(0,0,0); 


    const SimUnobservableStatisticsHeader::stat_map& statmap = unobservable->stats();
    SimUnobservableStatisticsHeader::stat_map::const_iterator unobIter, unobIterEnd = statmap.end();
    for(unobIter = statmap.begin(); unobIter!=unobIterEnd; unobIter++){
        if      (unobIter->first == "EDepInGdLS")   ibd->EDepInGdLS     = unobIter->second.sum();
        else if (unobIter->first == "EDepInLS")     ibd->EDepInLS       = unobIter->second.sum();
        else if (unobIter->first == "EDepInOIL")    ibd->EDepInOIL      = unobIter->second.sum();
        else if (unobIter->first == "QEDepInGdLS")  ibd->QEDepInGdLS    = unobIter->second.sum();
        else if (unobIter->first == "QEDepInLS")    ibd->QEDepInLS      = unobIter->second.sum();
        else if (unobIter->first == "QEDepInOIL")   ibd->QEDepInOIL     = unobIter->second.sum();
        //else if (unobIter->first == "capTarget_Trk2") ibd->capTarget    = unobIter->second.sum();
        else if (unobIter->first == "capTarget")    ibd->capTarget      = unobIter->second.sum();
        else if (unobIter->first == "capTargetMass")    ibd->capTargetMass      = unobIter->second.sum();
        else if (unobIter->first == "e_Trk1")       ibd->ept            = unobIter->second.mean();
        else if (unobIter->first == "xEnd_Trk1")    vtx_anni.SetX(unobIter->second.mean());
        else if (unobIter->first == "yEnd_Trk1")    vtx_anni.SetY(unobIter->second.mean());
        else if (unobIter->first == "zEnd_Trk1")    vtx_anni.SetZ(unobIter->second.mean());
        else if (unobIter->first == "xCap")         vtx_cap.SetX(unobIter->second.mean());
        else if (unobIter->first == "yCap")         vtx_cap.SetY(unobIter->second.mean());
        else if (unobIter->first == "zCap")         vtx_cap.SetZ(unobIter->second.mean());
    }


    Gaudi::XYZPoint glb_anni(vtx_anni.X(), vtx_anni.Y(), vtx_anni.Z());
    Gaudi::XYZPoint lcl_anni = m_dbOil1->geometry()->toLocal(glb_anni);
    Gaudi::XYZPoint glb_cap(vtx_cap.X(), vtx_cap.Y(), vtx_cap.Z());
    Gaudi::XYZPoint lcl_cap = m_dbOil1->geometry()->toLocal(glb_cap);


    // fill true vertex info in IBD struct
    ibd->xpt = lcl_anni.x();
    ibd->ypt = lcl_anni.y();
    ibd->zpt = lcl_anni.z();
    ibd->xdt = lcl_cap.x();
    ibd->ydt = lcl_cap.y();
    ibd->zdt = lcl_cap.z();


    // test
    int global_vol = 0;
    for(int i = 1; i<m_de.size(); i++){
        if(m_de.at(i)->geometry()->isInside(glb_cap)) global_vol = i;
        if(global_vol) break;
    }
    info() << "CapVolume = " << global_vol << endreq;
    ibd->capVol = global_vol;



    /*string capPart = m_dbOil1->geometry()->belongsToPath(lcl_cap,-1);
    info() << "Local belongs to path : " << capPart << endreq;
    IGeometryInfo* ginfo = m_dbOil1->geometry()->belongsTo(glb_cap);
    info() << "ginfo successful!" << endreq;*/


    return StatusCode::SUCCESS;
}
