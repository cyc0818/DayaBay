/**
 * Event Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#ifndef _EVENT_TREE_H_
#define _EVENT_TREE_H_

#include "TFile.h"
#include "TTree.h"
#include <iostream>

using namespace std;

#define Max 200

class EventTree
{
 public:
  /// Tree creation
  EventTree(const char* TreeName, const char* FileName, int BriefLevel);
  ~EventTree();
  
 public:
  /// Reset all numbers into Invalid
  int Reset();
  /// Fill one entries
  int Fill();
  /// Close the root file
  int Close();
  int Close(TH1D* h);

 public:
  
  /// Invalid number 
  const int    Invalid;

  /// Event information
  int    Run;
  int    Det;
  int    Fold;

  int    TrigSec;
  int    TrigNano;
    int    TrigNo;
  double E;
  double X;
  double Y;
  double Z;

    double T2PrevPlMu;
    double T2PrevAdMu;
    double T2PrevShMu;
    
    double LiveTime;
    double FullTime;
    double TimeGap;
    int AdMu;
    int ShMu;
    int WpMu;
    int NetMu;
    
    
 private:
  TFile* m_file;
  TTree* m_tree;
  
  int m_brief;
};

#endif  // _EVENT_TREE_H_
