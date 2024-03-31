/** 
 * Use vertex
 *
 * Jun 6, 2012 created by Zhe Wang
 */
#ifndef _EXAM_TRUTH_H_
#define _EXAM_TRUTH_H_
#include "GaudiAlg/GaudiAlgorithm.h"
#include "Event.h"
#include "EventTree.h"
#include "DetDesc/IGeometryInfo.h"
#include "DetDesc/DetectorElement.h"
#include "XYCorr.h"
#include "RZCorr.h"
#include <string>

class ExamTruth : public GaudiAlgorithm 
{

 public:
  
  ExamTruth(const std::string& name, ISvcLocator* pSvcLocator);
  virtual ~ExamTruth();
  
  virtual StatusCode initialize();
  virtual StatusCode execute();
  virtual StatusCode finalize();
  
 private:
  int        mDetSimCycle;
  Event      mEvent;
  EventTree* mTree;
  std::string mRootFile;

  StatusCode EndEvent();
    string getMaterial( Gaudi::XYZPoint ThisVtx );
    double m_RoavIn;
    double    m_Rshield;
    double  m_ZreflectorTop;
    double  m_ZreflectorBottom;

  /// Others
  //IDetectorElement *m_dbOil1;
  //IDetectorElement *m_dbLso1;

  /// Materials
  Material *m_Oil;
  Material *m_Lso;
  Material *m_Gds;
  Material *m_Acr;
  Material *m_Sst;
  Material *m_Alk;
  Material *m_Pyr;
  Material *m_Esr;  

  /// Detector Elements
    IDetectorElement *m_dyb;
    IDetectorElement *m_dbOil1;
    IDetectorElement *m_dbLso1;
    IDetectorElement *m_dbGds1;
    IDetectorElement *m_dbIav1;
    IDetectorElement *m_dbOav1;
    IDetectorElement *m_dbSst1;
    IDetectorElement *m_dbTube;
    IDetectorElement *m_target_de_name;



  /// RZCorr
  int Corr;
  RZCorr * mRZCorr;
  XYCorr * mXYCorr;
    bool lastSimInfo;
};

#endif  // _EXAM_TRUTH_H_
