/** 
 * MyPromptEfficiencyAlg
 *
 * Apr 28, 2010  Created by ...
 */

#ifndef _MYPROMPTEFFICIENCYALG_H_
#define _MYPROMPTEFFICIENCYALG_H_

#define SIMREADTIMES_oil 0 
#define SIMREADTIMES_lso 1
#define SIMREADTIMES_gds 2
#define SIMREADTIMES_acrylic 3
#define SIMREADTIMES_fullvol 4

#define MAXMCHISTS 5

#include "GaudiAlg/GaudiAlgorithm.h"
#include "Context/TimeStamp.h"
#include "Conventions/Detectors.h"
#include "DetDesc/IGeometryInfo.h"
#include "DetDesc/DetectorElement.h"
#include "DetDesc/IDetectorElement.h"
#include "Event/GenHeader.h"
#include "Event/SimHeader.h"
#include "Event/RecHeader.h"
#include "Event/UserDataHeader.h"
#include <vector>
#include <map>
#include <string>
#include "TH1.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TList.h"
#include "TVector3.h"

class IStatisticsSvc;
class TH1;
struct IBDpair{
    int genType;
    int capTarget;
    int capTargetMass;
    int capVol;

    double EDepInGdLS;
    double EDepInLS;
    double EDepInOIL;

    double QEDepInGdLS;
    double QEDepInLS;
    double QEDepInOIL;

    double DepositedEnergy;
    double QuenchedEnergy;
    //double SumHitsEnergy;

    double ep, ept;
    double xp, xpt;
    double yp, ypt;
    double zp, zpt;
    long long tp;

    double ed;
    double xd, xdt;
    double yd, ydt;
    double zd, zdt;
    long long td;

    double e3;
    double x3;
    double y3;
    double z3;
    long long t3;

    bool ready;
    bool isPromptFlasher;
    bool isDelayFlasher;
    bool isThirdFlasher;
};

struct nCapture{

    int vol_gen;
    TVector3 vtx_gen;
    double KE_gen;

    int vol_sct;
    TVector3 vtx_sct;
    double KE_bfcap;

    int vol_cap;
    TVector3 vtx_cap;
    double KE_cap;

    int CapTarget;
    int CapTargetMass;


};
    


class MyPromptEfficiencyAlg : public GaudiAlgorithm 
{

 public:
  
  MyPromptEfficiencyAlg(const std::string& name, ISvcLocator* pSvcLocator);
  virtual ~MyPromptEfficiencyAlg();
  
  virtual StatusCode initialize();
  virtual StatusCode execute();
  virtual StatusCode finalize();

  
 private:

    // Handle for statistics service
    int executionIndex;
    int run_Number;
    int N_gen[MAXMCHISTS];
    int N_lastsct[6];
    int N_cap[6];
    int N_double[MAXMCHISTS];
    std::map<int,int> N_gen_map[MAXMCHISTS];

    TTree* m_tree;
    TTree* m_ibd_tree;
    TTree* m_ncap_tree;
    IStatisticsSvc* m_statsSvc;
    IDetectorElement* m_dbOil1;
    std::vector<IDetectorElement*> m_de;
    std::vector<nCapture> nCapV;
    std::map<int, TH1**> m_shortCuts;
    std::map<int, IBDpair*> IBDmap;
  
    TH1* getOrMakeHist(int run,int histCode);
    std::string getPath(int run, const char* histName);
    int judgeGeneratorName(const std::string& generatorName);
    StatusCode processGenHeader();
    StatusCode fillFinalTree(int run);
    StatusCode fillIBDstruct(struct IBDpair*, int, DayaBay::RecTrigger&);
    StatusCode fillIBDTree();
    bool isFlasher(DayaBay::UserDataHeader*, const DayaBay::RecTrigger&);
    StatusCode fillIBDunobservableStatistics(struct IBDpair*, const DayaBay::SimHeader*);
};
////Class AdSimple's area////
#endif  // _MYPROMPTEFFICIENCYALG_H_
