/**
 * Event Tree
 *
 * Nov. 10, 2011 Created by Zhe Wang
 */

#include "EventTree.h"

#include <sstream>

EventTree::EventTree(const char* TreeName, const char* FileName, int BriefLevel)
  :Invalid(0)
{
  m_file = new TFile(FileName,"recreate");
  m_tree = new TTree(TreeName,"Analysis Tree");    /// create tree
  m_brief = BriefLevel;
  
  /// No spliting
  /// m_tree->SetMaxTreeSize(500000000);  // 500M

  /// Tree entry information
  /// For delayed signal
  m_tree->Branch( "Run",          &Run,          "Run/I"          );
  m_tree->Branch( "Det",          &Det,          "Det/I"          );
  m_tree->Branch( "Fold",         &Fold,         "Fold/I"         );

  m_tree->Branch( "TrigSec",      &TrigSec,       "TrigSec/I"       );
  m_tree->Branch( "TrigNano",     &TrigNano,      "TrigNano/I"      );
  m_tree->Branch( "TrigNo",     &TrigNo,      "TrigNo/I"      );
    
    m_tree->Branch( "AdMu",      &AdMu,       "AdMu/I"       );
    m_tree->Branch( "ShMu",      &ShMu,       "ShMu/I"       );
    m_tree->Branch( "WpMu",      &WpMu,       "WpMu/I"       );
    m_tree->Branch( "NetMu",     &NetMu,      "NetMu/I"       );
    
  m_tree->Branch( "E",            &E,             "E/D"             );
  m_tree->Branch( "X",            &X,             "X/D"             );
  m_tree->Branch( "Y",            &Y,             "Y/D"             );
  m_tree->Branch( "Z",            &Z,             "Z/D"             );

    m_tree->Branch( "T2PrevPlMu",   &T2PrevPlMu,   "T2PrevPlMu/D"   );
    m_tree->Branch( "T2PrevAdMu",   &T2PrevAdMu,   "T2PrevAdMu/D"   );
    m_tree->Branch( "T2PrevShMu",   &T2PrevShMu,   "T2PrevShMu/D"   );
    m_tree->Branch( "LiveTime",     &LiveTime,     "LiveTime/D"   );
    m_tree->Branch( "FullTime",     &FullTime,     "FullTime/D"   );
    m_tree->Branch( "TimeGap",     &TimeGap,     "TimeGap/D"   );
    
    
}

EventTree::~EventTree()
{}

int EventTree::Reset()
{
  Run = Invalid;
  Det = Invalid;
    Fold = Invalid;
    TrigSec = Invalid;
    TrigNano = Invalid;
    TrigNo = Invalid;
    E = Invalid;
    X = Invalid;
    Y = Invalid;
    Z = Invalid;

    T2PrevPlMu = Invalid;
    T2PrevAdMu = Invalid;
    T2PrevShMu = Invalid;
    
    LiveTime   = Invalid;
    FullTime   = Invalid;
    
    AdMu   = Invalid;
    ShMu   = Invalid;
    WpMu   = Invalid;
    NetMu  = Invalid;
  return 1;  // 1 for SUCCESS;
}

int EventTree::Fill()
{
  m_tree->Fill();
  
  return  1; // 1 for SUCCESS;
}

int EventTree::Close()
{
  // Pay attention to the last line. It is necessary to file splitting.
  // http://root.cern.ch/root/htmldoc/TTree.html#TTree:ChangeFile
  m_file = m_tree->GetCurrentFile(); //to get the pointer to the current file
  //m_file->Write();
  m_file->Write(0,TObject::kOverwrite);


  return  1; // 1 for SUCCESS;
}


int EventTree::Close(TH1D* h)
{

  m_file->cd();
  m_tree->Write();
  if(h) h->Write();
  m_file->Close();


  return  1; // 1 for SUCCESS;
}

