/**
 * Check IBD sample
 *
 * Jun 4, 2012 created by Zhe Wang
 */
#include "ExamTruth.h"

#include "CLHEP/Units/SystemOfUnits.h"
#include "DetDesc/Material.h"
// for SimHit
#include "Event/SimHitHeader.h"
#include "Event/SimHitCollection.h"
#include "Event/SimPmtHit.h"
#include "Event/SimHit.h"
// for history info
//#include "Event/SimParticleHistoryHeader.h"
#include "Event/SimParticleHistory.h"
#include "Event/SimUnobservableStatisticsHeader.h"
#include "Event/SimStatistic.h"
// for RecHeader
#include "Event/RecHeader.h"

using namespace std;
using namespace DayaBay;

ExamTruth::ExamTruth(const std::string& name, ISvcLocator* pSvcLocator):
  GaudiAlgorithm(name, pSvcLocator)
{
  declareProperty("RootFile", mRootFile = "test.TWin.root", "Output root file name");
  declareProperty("XYZCorr",  Corr = 0, "By default no correction");

  mRZCorr = new RZCorr;
  mXYCorr = new XYCorr;
}

ExamTruth::~ExamTruth()
{
}

StatusCode ExamTruth::initialize()
{
  mDetSimCycle = -1;
  mTree = new EventTree( "Event", mRootFile.c_str(), 0);

  m_dyb    = getDet<IDetectorElement>("/dd/Structure/DayaBay");
  m_dbOil1 = getDet<IDetectorElement>("/dd/Structure/AD/db-oil1");
  m_dbLso1 = getDet<IDetectorElement>("/dd/Structure/AD/db-lso1");


  this->GaudiAlgorithm::initialize();
  return StatusCode::SUCCESS;
}

StatusCode ExamTruth::execute()
{
  /// The reconstructed info
  /// ----------------------
  /* AdSimple has been tried. The grid structure is too obvious. */
  RecHeader* pRecHeader = get<RecHeader>( "/Event/Rec/AdSimple" );
  if(!pRecHeader) {
    error()<<"Failed to get RecHeader"<<endreq;
    return StatusCode::FAILURE;
  }

  /// Get RecTrigger
  const RecTrigger* pRecTrigger = &(pRecHeader->recTrigger());
  if(!pRecTrigger) {
    error()<<"Failed to get RecTrigger"<<endreq;
    return StatusCode::FAILURE;
  }

  /// Trigger time
  TimeStamp TrigTime ( pRecTrigger->triggerTime().GetSec(), pRecTrigger->triggerTime().GetNanoSec() );
  double E = pRecTrigger->energy();
  double recX = pRecTrigger->position().x();
  double recY = pRecTrigger->position().y();
  double recZ = pRecTrigger->position().z();

  double X,Y,Z,R2;

  double recR2 = pow(recX,2)+pow(recY,2);

  if( Corr ) {
    //mXYCorr->Correct( recX, recY, X, Y );
    X = recX;
    Y = recY;
    mRZCorr->Correct( recZ, recR2, Z, R2 );
  } else {
    X = recX;
    Y = recY;
    Z = recZ;
    R2 = recR2;
  }

  //cout<<"ReconINFO: "<<E<<endl;
  /// Find its MC truth info
  /// ----------------------
  const vector<const IHeader*> IList = pRecHeader->findHeaders( SimHeader::classID() );
  if( IList.size() == 0 )  {
    warning()<<"Failed to get its corresponding SimHeaders. Skipped."<<endreq;
    return StatusCode::SUCCESS;
  }
  if( IList.size() >= 2 )  {
    warning()<<"Get more than 1 SimHeaders. Skipped to avoid ambiguity."<<endreq;
    return StatusCode::SUCCESS;
  }

  /// Get the only one SimHeader
  const SimHeader* pSimHeader = dynamic_cast<const SimHeader*>( *(IList.begin()) );
  int ThisSimCycle = pSimHeader->execNumber();
  //info()<<ThisSimCycle<<endreq;

  //Get UnObservable Statistics info
  const DayaBay::SimUnobservableStatisticsHeader* pUnobs =
    pSimHeader->unobservableStatistics();
  const DayaBay::SimUnobservableStatisticsHeader::stat_map&
    statmap = pUnobs->stats();
  DayaBay::SimUnobservableStatisticsHeader::stat_map::const_iterator
    st, stdone = statmap.end();

  /// Find tCap
  /// ---------
  double tCap;  /* in ns */
  double xCap, yCap, zCap, capTarget;
  double Ekfromsim;
  int capTargetMass;
  
  /// Positron info
  int pdgId_Trk1;
  double x_Trk1, y_Trk1, z_Trk1, e_Trk1;

  if( !pUnobs ) {
    warning()<<"Failed to get SimParticleHistory. Skipped."<<endreq;
    return StatusCode::SUCCESS;

  } else {
    
    /// About neutron capture
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="tCap")   tCap = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="xCap")   xCap = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="yCap")   yCap = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="zCap")   zCap = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="capTarget")   capTarget = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="capTargetMass")   capTargetMass = (int)st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="ke_Trk2")   Ekfromsim = st->second.mean();
    }

    /// About positron initial info
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="pdgId_Trk1")   pdgId_Trk1 = (int)st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="e_Trk1")   e_Trk1 = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="x_Trk1")   x_Trk1 = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="y_Trk1")   y_Trk1 = st->second.mean();
    }
    for (st=statmap.begin(); st != stdone; ++st) {
      if(st->first=="z_Trk1")   z_Trk1 = st->second.mean();
    }

  }

  /// Check parentPDG
  int PDG0;
  //PDG0 = 

  /// Just confirm track 1 is positron
  if( pdgId_Trk1 != -11 )  {
    warning()<<"Track 1 is not positron. Can't get positron truth. Skipped."<<endreq;
    return StatusCode::SUCCESS;
  }

  /// Truth vertex transformation to local cooridinates.
  Gaudi::XYZPoint GblGen( x_Trk1, y_Trk1, z_Trk1 );
  Gaudi::XYZPoint LclGen = m_dbOil1->geometry()->toLocal( GblGen );

  Gaudi::XYZPoint GblCap( xCap, yCap, zCap );
  Gaudi::XYZPoint LclCap = m_dbOil1->geometry()->toLocal( GblCap );
    
    ////
    Gaudi::XYZPoint LclThis = m_dyb->geometry()->toLocal( GblGen );
    string genPart = m_dyb->geometry()->belongsToPath( LclThis, -1 );
    IDetectorElement *genDe = getDet<IDetectorElement>( genPart );
    string genDetMar = genDe->geometry()->lvolume()->material()->name();
    int    CrrDepVol  = 0;
    
    if (genDetMar=="GdDopedLS") {
        CrrDepVol = 1;
    }else if (genDetMar=="LiquidScintillator") {
        CrrDepVol = 2;
    }else if (genDetMar=="Acrylic") {
        CrrDepVol = 3;
    }else if (genDetMar=="MineralOil") {
        CrrDepVol = 4;
    }else {
        CrrDepVol = 0;
    }
    ////
    Gaudi::XYZPoint LcCapThis = m_dyb->geometry()->toLocal( GblCap );
    string capPart = m_dyb->geometry()->belongsToPath( LcCapThis, -1 );
    IDetectorElement *capDe = getDet<IDetectorElement>( capPart );
    string capDetMar = capDe->geometry()->lvolume()->material()->name();
    int    CapDepVol  = 0;
    //cout<<"cap: "<<capDetMar<<endl;  
    if (capDetMar=="GdDopedLS") {
        CapDepVol = 1;
    }else if (capDetMar=="LiquidScintillator") {
        CapDepVol = 2;
    }else if (capDetMar=="Acrylic") {
        CapDepVol = 3;
    }else if (capDetMar=="MineralOil") {
        CapDepVol = 4;
    }else {
        CapDepVol = 0;
    }

    
    //cout<<CrrDepVol<<endl;
    ////
  /// CapT and GenT
  TimeStamp GenT = pSimHeader->timeStamp();          /* Abs generation time */
  TimeStamp CapT = GenT;  CapT.Add(tCap/1e9);        /* Abs capture time    */

  static int lastSim=-1;
  if( tCap < 1e3 )  {
    int Sim = pSimHeader->execNumber();
    if( Sim != lastSim ) {
      warning()<<" One candidate with CapT<1e3 ns "<<endreq;
      lastSim = Sim;
    }
    warning()<<"CapT and GenT are too closed. Skipped."<<endreq;
    //return StatusCode::SUCCESS;
  }

  /// The first interaction vertex of the 2.2 MeV gamma
  const DayaBay::SimParticleHistory* pHist = pSimHeader->particleHistory();

  if( !pHist ) {
    warning()<<"Can't get the history info"<<endreq;
    return StatusCode::SUCCESS;
  }

    /*
 
  // Search for the 2.2 MeV SimTrack
  const std::list<DayaBay::SimTrack*>& trk=pHist->tracks();
  std::list<DayaBay::SimTrack*>::const_iterator tkci, tkEnd=trk.end();
  //cout<<" list size: "<<trk.size()<<endl;
  SimTrack* InteristTrack = 0;
  for(tkci = trk.begin(); tkci != tkEnd; tkci++ ) {
	InteristTrack = *tkci;
     //cout<<" TEST partical ID: "<<(*tkci)->particle()<<endl;
     //cout<<" TEST vertex: "<<(*tkci)->vertices().size()<<endl;
  	/// Looking for the first interaction point
  	const vector<SimVertex*>& GamVtx = InteristTrack->vertices();
  	const SimVertex* FirstComptonVtx = 0;
  	Gaudi::XYZPoint  AveGammaVtx(0,0,0);
  	double ETotal, EAtLastVtx, ELoss;
  	int vn = GamVtx.size()-1;
  	info()<<GamVtx[vn]->time()<<"\t"<<GamVtx[vn]->process().name()<<"\t"<<GamVtx[vn]->totalEnergy()<<endreq;
  	double vtCap = GamVtx[vn]->time();
  	TimeStamp CapT2 = GenT;  CapT2.Add(vtCap/1e9);    
  	//cout<<" compareT: "<<abs((TrigTime-CapT2).GetSeconds())<<endl;
  }

  */
    double Eki = 0; 
    double Ekf = 0; 


    const list<DayaBay::SimTrack*> trk=pHist->tracks();
    for(list<DayaBay::SimTrack*>::const_iterator itr = trk.begin(); itr!=trk.end(); itr++){
        
        if((*itr)->particle() != 2112) continue;
        const vector<SimVertex*> ptclVtx = (*itr)->vertices();


        vector<SimVertex*>::const_iterator init_vtx = ptclVtx.begin();
        vector<SimVertex*>::const_iterator bfc_vtx = ptclVtx.end()-2;   // before neutron capture (last scattering)
        if(ptclVtx.size() < 2){
            bfc_vtx = init_vtx;
            info() << "No scattering before captured" << endreq;
        }
        info() << "Neutron Kinetic Energy : Initial = " << (*init_vtx)->kineticEnergy() << " , Final = " << (*bfc_vtx)->kineticEnergy() << endreq;


        Eki = (*init_vtx)->kineticEnergy();
        Ekf = (*bfc_vtx)->kineticEnergy();

    }


  /// Finish an event and restart
  /// ---------------------------

  //cout<<"--- finish check: "<<ThisSimCycle<<"\t"<<mDetSimCycle<<endl;
  if( ThisSimCycle != mDetSimCycle )  {
    if( mDetSimCycle != -1 )  {
      EndEvent();
    }
    mDetSimCycle = ThisSimCycle;
    mEvent.Reset();
  }

  //cout<<"--------  preTest: "<<abs((TrigTime-GenT).GetSeconds())<<" "<<abs((TrigTime-CapT).GetSeconds())<<endl;
  /// Positron branch
  /// ---------------
  if( abs((TrigTime-GenT).GetSeconds()) < 0.1e-6 ) {

    /* Is this a bug to set it to 1 here? */
    /* Always set positron to the first?  */
    mEvent.Fold = 1;

    //cout<<"-- check code --- Positron: "<<abs((TrigTime-GenT).GetSeconds())<<" num of Fold: "<<mEvent.Fold<<endl;
    // AddElectron
    mEvent.TrigSec[0]  = TrigTime.GetSec();
    mEvent.TrigNano[0] = TrigTime.GetNanoSec();
    mEvent.E[0]        = E;
    mEvent.X[0]        = X;
    mEvent.Y[0]        = Y;
    mEvent.Z[0]        = Z;
    mEvent.D2First[0]  = 0;

    // Truth
    mEvent.TrigSecT[0]  = GenT.GetSec();
    mEvent.TrigNanoT[0] = GenT.GetNanoSec();
    mEvent.ET[0]        = e_Trk1 + 0.511; /* Kinetic Energy + 0.511 */
    mEvent.XT[0]        = LclGen.x();   /* Trac 1215 */
    mEvent.YT[0]        = LclGen.y();
    mEvent.ZT[0]        = LclGen.z();
    mEvent.D2FirstT[0]  = 0;

  }

  /// Neutron branch
  /// --------------
  mEvent.GenDet = CrrDepVol;
  mEvent.CapDet = CapDepVol;
  mEvent.CapTarget = capTarget;
  mEvent.CapTargetMass = capTargetMass;
  mEvent.EkInit = Eki;
  mEvent.EkBfCap = Ekf;
  mEvent.EkMean = Ekfromsim;
  if( abs((TrigTime-CapT).GetSeconds()) < 0.1e-6 ) {

    mEvent.Fold += 1;
    int Fold = mEvent.Fold-1;  /* for array idx */
    //cout<<"-- check code --- Neutron: "<<abs((TrigTime-CapT).GetSeconds())<<" num of Fold: "<<mEvent.Fold<<endl;

    // AddNeutron
    double X1,Y1,Z1;
    X1  = mEvent.X[ 0 ];
    Y1  = mEvent.Y[ 0 ];
    Z1  = mEvent.Z[ 0 ];

    mEvent.TrigSec[Fold]  = TrigTime.GetSec();
    mEvent.TrigNano[Fold] = TrigTime.GetNanoSec();
    mEvent.E[Fold]        = E;
    mEvent.X[Fold]        = X;
    mEvent.Y[Fold]        = Y;
    mEvent.Z[Fold]        = Z;
    mEvent.D2First[Fold]  = sqrt( (X-X1)*(X-X1) + (Y-Y1)*(Y-Y1) + (Z-Z1)*(Z-Z1) );

    // Truth
    X1  = mEvent.XT[ 0 ];
    Y1  = mEvent.YT[ 0 ];
    Z1  = mEvent.ZT[ 0 ];

    mEvent.TrigSecT[Fold]  = CapT.GetSec();
    mEvent.TrigNanoT[Fold] = CapT.GetNanoSec();

    mEvent.ET[Fold] = capTarget;
    if( capTarget == 1 )   mEvent.ET[Fold] = 2.2246;
    if( capTarget == 6 )   mEvent.ET[Fold] = 5.5;
    if( capTarget == 64 )  mEvent.ET[Fold] = 8.1;

    mEvent.XT[Fold]        = LclCap.x(); //- LclCap.x();
    mEvent.YT[Fold]        = LclCap.y(); //- LclCap.y();
    mEvent.ZT[Fold]        = LclCap.z();
    mEvent.D2FirstT[Fold]  = sqrt( ( mEvent.XT[Fold]-X1)*(mEvent.XT[Fold]-X1) 
				   + (mEvent.YT[Fold]-Y1)*(mEvent.YT[Fold]-Y1) 
				   + (mEvent.ZT[Fold]-Z1)*(mEvent.ZT[Fold]-Z1) );

    mEvent.XDepC[Fold]      = 0;//- LclDepC.x();
    mEvent.YDepC[Fold]      = 0;//- LclDepC.y();
    mEvent.ZDepC[Fold]      = 0;//LclDepC.z();
    
    mEvent.T2PrevSubEvt[Fold] = (mEvent.TrigSecT[Fold]-mEvent.TrigSecT[Fold-1])+
      (mEvent.TrigNanoT[Fold]-mEvent.TrigNanoT[Fold-1])*1e-9;
  }

  return StatusCode::SUCCESS;
}

StatusCode ExamTruth::finalize()
{
  mTree->Close();
  return this->GaudiAlgorithm::finalize();
}

StatusCode ExamTruth::EndEvent()
{
  mTree->Reset();

  mTree->Run        = 0;
  mTree->Det        = 0;

  mTree->T2PrevMu   = 0;
  mTree->T2PrevPlMu = 0;
  mTree->T2PrevAdMu = 0;
  mTree->T2PrevShMu = 0;
  mTree->T2PrevNetMu = 0;
  

  mTree->Fold       = mEvent.Fold;
  if( mEvent.Fold > Max ) {
    warning()<<"Number of fold is above the limit. Skipped."<<endreq;
    return StatusCode::SUCCESS;
  }

  for( int FoldIdx = 0; FoldIdx < mEvent.Fold; FoldIdx++ )   {
    mTree->TrigSec[FoldIdx]      = mEvent.TrigSec[FoldIdx];
    mTree->TrigNano[FoldIdx]     = mEvent.TrigNano[FoldIdx];
    mTree->E[FoldIdx]            = mEvent.E[FoldIdx];
    mTree->X[FoldIdx]            = mEvent.X[FoldIdx];
    mTree->Y[FoldIdx]            = mEvent.Y[FoldIdx];
    mTree->Z[FoldIdx]            = mEvent.Z[FoldIdx];
    mTree->D2First[FoldIdx]      = mEvent.D2First[FoldIdx];
    mTree->T2PrevSubEvt[FoldIdx] = mEvent.T2PrevSubEvt[FoldIdx];

    mTree->TrigSecT[FoldIdx]      = mEvent.TrigSecT[FoldIdx];
    mTree->TrigNanoT[FoldIdx]     = mEvent.TrigNanoT[FoldIdx];
    mTree->ET[FoldIdx]            = mEvent.ET[FoldIdx];
    mTree->XT[FoldIdx]            = mEvent.XT[FoldIdx];
    mTree->YT[FoldIdx]            = mEvent.YT[FoldIdx];
    mTree->ZT[FoldIdx]            = mEvent.ZT[FoldIdx];
    mTree->D2FirstT[FoldIdx]      = mEvent.D2FirstT[FoldIdx];
    mTree->T2PrevSubEvtT[FoldIdx] = mEvent.T2PrevSubEvtT[FoldIdx];

    mTree->XDepC[FoldIdx]          = mEvent.XDepC[FoldIdx];
    mTree->YDepC[FoldIdx]          = mEvent.YDepC[FoldIdx];
    mTree->ZDepC[FoldIdx]          = mEvent.ZDepC[FoldIdx];
    mTree->CapTarget               = mEvent.CapTarget;
    mTree->CapTargetMass           = mEvent.CapTargetMass;
    mTree->GenDet                  = mEvent.GenDet;
    mTree->CapDet                  = mEvent.CapDet;
    mTree->EkInit                  = mEvent.EkInit;
    mTree->EkBfCap                 = mEvent.EkBfCap;
    mTree->EkMean                  = mEvent.EkMean;
  }
  
  // For beizhen
  if( mEvent.Fold==1 ) {
    mTree->Fold       = 2;
    mTree->E[1]       = 0;
  } 

  mTree->Fill();

  return StatusCode::SUCCESS;
}  
