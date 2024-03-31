//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Sep 18 13:55:47 2012 by ROOT version 5.32/00
// from TTree CalibReadoutHeader/Tree at /Event/CalibReadout/CalibReadoutHeader holding CalibReadout_CalibReadoutHeader
// found on file: recon.Neutrino.0021221.Physics.EH1-Merged.P12B-I._0010.root
//////////////////////////////////////////////////////////

#ifndef CalibReadoutHeader_h
#define CalibReadoutHeader_h

#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TTimeStamp.h"
#include <vector>

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.
//const Int_t kMaxinputHeaders = 1;

class CalibReadoutHeader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //PerCalibReadoutHeader *CalibReadout_CalibReadoutHeader;
   Int_t           clID;
   Int_t           earliest_mSec;
   Int_t           earliest_mNanoSec;
   Int_t           latest_mSec;
   Int_t           latest_mNanoSec;
   Int_t           context_mSite;
   Int_t           context_mSimFlag;
   Int_t           context_mTimeStamp_mSec;
   Int_t           context_mTimeStamp_mNanoSec;
   Int_t           context_mDetId;
   Int_t           execNumber;
   UInt_t          jobId_m_data[4];
   vector<unsigned long> randomState;
   Int_t           inputHeaders_;
   //Int_t           inputHeaders_m_entry[kMaxinputHeaders];   //[inputHeaders_]
   //string          inputHeaders_m_path[kMaxinputHeaders];
   UInt_t          site;
   UInt_t          detector;
   UInt_t          triggerNumber;
   UInt_t          triggerType;
   UInt_t          triggerTimeSec;
   UInt_t          triggerTimeNanoSec;
//   TTimeStamp	   trigggerTime;
   UInt_t          nHitsAD;
   vector<float>   timeAD;
   vector<float>   chargeAD;
   vector<unsigned int> hitCountAD;
   vector<unsigned int> ring;
   vector<unsigned int> column;
   UInt_t          nHitsAD_calib;
   vector<float>   timeAD_calib;
   vector<float>   chargeAD_calib;
   vector<unsigned int> hitCountAD_calib;
   vector<unsigned int> topOrBottom;
   vector<unsigned int> acuColumn;
   UInt_t          nHitsPool;
   vector<float>   timePool;
   vector<float>   chargePool;
   vector<unsigned int> hitCountPool;
   vector<unsigned int> wallNumber;
   vector<unsigned int> wallSpot;
   vector<unsigned int> inwardFacing;
   UInt_t          nHitsRpc;
   vector<unsigned int> rpcRow;
   vector<unsigned int> rpcColumn;
   vector<unsigned int> rpcLayer;
   vector<unsigned int> rpcStrip;
   vector<bool>    rpcFromRot;


   TTimeStamp muon_trigTime;
   bool is_AD_muon;
   bool is_Shower_muon;
   bool is_IWS_muon;
   bool is_OWS_muon;

   void MuonVetoWindow();
   bool MuonTag( int nHit_frm_CalibStats, float rawEvis_frm_Adrec);


   TTimeStamp MuonWindowBegin;
   TTimeStamp MuonWindowEnd;

   // List of branches
   TBranch        *b_CalibReadout_CalibReadoutHeader_clID;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_earliest_mSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_earliest_mNanoSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_latest_mSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_latest_mNanoSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_context_mSite;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_context_mSimFlag;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_context_mTimeStamp_mSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_context_mTimeStamp_mNanoSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_context_mDetId;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_execNumber;   //!
//   TBranch        *b_CalibReadout_CalibReadoutHeader_jobId_m_data;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_randomState;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_inputHeaders_;   //!
   //TBranch        *b_inputHeaders_m_entry;   //!
//   TBranch        *b_inputHeaders_m_path;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_site;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_detector;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_triggerNumber;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_triggerType;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_triggerTimeSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_triggerTimeNanoSec;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_nHitsAD;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_timeAD;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_chargeAD;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_hitCountAD;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_ring;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_column;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_nHitsAD_calib;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_timeAD_calib;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_chargeAD_calib;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_hitCountAD_calib;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_topOrBottom;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_acuColumn;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_nHitsPool;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_timePool;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_chargePool;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_hitCountPool;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_wallNumber;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_wallSpot;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_inwardFacing;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_nHitsRpc;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_rpcRow;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_rpcColumn;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_rpcLayer;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_rpcStrip;   //!
   TBranch        *b_CalibReadout_CalibReadoutHeader_rpcFromRot;   //!

   CalibReadoutHeader(TTree *tr);
   virtual ~CalibReadoutHeader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

    /*
   CalibReadoutHeader(TTree *tr);
   Int_t    Cut(Long64_t entry);
   Int_t    GetEntry(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void     Init(TTree *tree);
   void     Loop();
   Bool_t   Notify();
   void     Show(Long64_t entry = -1);
    */
};

#endif

#ifdef CalibReadoutHeader_cxx

CalibReadoutHeader::CalibReadoutHeader(TTree *tr)
{
    Init(tr);
}

//CalibReadoutHeader::CalibReadoutHeader(TFile *ifile)

CalibReadoutHeader::~CalibReadoutHeader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CalibReadoutHeader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CalibReadoutHeader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void CalibReadoutHeader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("clID", &clID, &b_CalibReadout_CalibReadoutHeader_clID);
   fChain->SetBranchAddress("earliest.mSec", &earliest_mSec, &b_CalibReadout_CalibReadoutHeader_earliest_mSec);
   fChain->SetBranchAddress("earliest.mNanoSec", &earliest_mNanoSec, &b_CalibReadout_CalibReadoutHeader_earliest_mNanoSec);
   fChain->SetBranchAddress("latest.mSec", &latest_mSec, &b_CalibReadout_CalibReadoutHeader_latest_mSec);
   fChain->SetBranchAddress("latest.mNanoSec", &latest_mNanoSec, &b_CalibReadout_CalibReadoutHeader_latest_mNanoSec);
   fChain->SetBranchAddress("context.mSite", &context_mSite, &b_CalibReadout_CalibReadoutHeader_context_mSite);
   fChain->SetBranchAddress("context.mSimFlag", &context_mSimFlag, &b_CalibReadout_CalibReadoutHeader_context_mSimFlag);
   fChain->SetBranchAddress("context.mTimeStamp.mSec", &context_mTimeStamp_mSec, &b_CalibReadout_CalibReadoutHeader_context_mTimeStamp_mSec);
   fChain->SetBranchAddress("context.mTimeStamp.mNanoSec", &context_mTimeStamp_mNanoSec, &b_CalibReadout_CalibReadoutHeader_context_mTimeStamp_mNanoSec);
   fChain->SetBranchAddress("context.mDetId", &context_mDetId, &b_CalibReadout_CalibReadoutHeader_context_mDetId);
   fChain->SetBranchAddress("execNumber", &execNumber, &b_CalibReadout_CalibReadoutHeader_execNumber);
//   fChain->SetBranchAddress("jobId.m_data[4]", jobId_m_data, &b_CalibReadout_CalibReadoutHeader_jobId_m_data);
   fChain->SetBranchAddress("randomState", &randomState, &b_CalibReadout_CalibReadoutHeader_randomState);
   fChain->SetBranchAddress("inputHeaders", &inputHeaders_, &b_CalibReadout_CalibReadoutHeader_inputHeaders_);
   //fChain->SetBranchAddress("inputHeaders.m_entry", &inputHeaders_m_entry, &b_inputHeaders_m_entry);
//   fChain->SetBranchAddress("inputHeaders.m_path", &inputHeaders_m_path, &b_inputHeaders_m_path);
   fChain->SetBranchAddress("site", &site, &b_CalibReadout_CalibReadoutHeader_site);
   fChain->SetBranchAddress("detector", &detector, &b_CalibReadout_CalibReadoutHeader_detector);
   fChain->SetBranchAddress("triggerNumber", &triggerNumber, &b_CalibReadout_CalibReadoutHeader_triggerNumber);
   fChain->SetBranchAddress("triggerType", &triggerType, &b_CalibReadout_CalibReadoutHeader_triggerType);
   fChain->SetBranchAddress("triggerTimeSec", &triggerTimeSec, &b_CalibReadout_CalibReadoutHeader_triggerTimeSec);
   fChain->SetBranchAddress("triggerTimeNanoSec", &triggerTimeNanoSec, &b_CalibReadout_CalibReadoutHeader_triggerTimeNanoSec);
   fChain->SetBranchAddress("nHitsAD", &nHitsAD, &b_CalibReadout_CalibReadoutHeader_nHitsAD);
   fChain->SetBranchAddress("timeAD", &timeAD, &b_CalibReadout_CalibReadoutHeader_timeAD);
   fChain->SetBranchAddress("chargeAD", &chargeAD, &b_CalibReadout_CalibReadoutHeader_chargeAD);
   fChain->SetBranchAddress("hitCountAD", &hitCountAD, &b_CalibReadout_CalibReadoutHeader_hitCountAD);
   fChain->SetBranchAddress("ring", &ring, &b_CalibReadout_CalibReadoutHeader_ring);
   fChain->SetBranchAddress("column", &column, &b_CalibReadout_CalibReadoutHeader_column);
   fChain->SetBranchAddress("nHitsAD_calib", &nHitsAD_calib, &b_CalibReadout_CalibReadoutHeader_nHitsAD_calib);
   fChain->SetBranchAddress("timeAD_calib", &timeAD_calib, &b_CalibReadout_CalibReadoutHeader_timeAD_calib);
   fChain->SetBranchAddress("chargeAD_calib", &chargeAD_calib, &b_CalibReadout_CalibReadoutHeader_chargeAD_calib);
   fChain->SetBranchAddress("hitCountAD_calib", &hitCountAD_calib, &b_CalibReadout_CalibReadoutHeader_hitCountAD_calib);
   fChain->SetBranchAddress("topOrBottom", &topOrBottom, &b_CalibReadout_CalibReadoutHeader_topOrBottom);
   fChain->SetBranchAddress("acuColumn", &acuColumn, &b_CalibReadout_CalibReadoutHeader_acuColumn);
   fChain->SetBranchAddress("nHitsPool", &nHitsPool, &b_CalibReadout_CalibReadoutHeader_nHitsPool);
   fChain->SetBranchAddress("timePool", &timePool, &b_CalibReadout_CalibReadoutHeader_timePool);
   fChain->SetBranchAddress("chargePool", &chargePool, &b_CalibReadout_CalibReadoutHeader_chargePool);
   fChain->SetBranchAddress("hitCountPool", &hitCountPool, &b_CalibReadout_CalibReadoutHeader_hitCountPool);
   fChain->SetBranchAddress("wallNumber", &wallNumber, &b_CalibReadout_CalibReadoutHeader_wallNumber);
   fChain->SetBranchAddress("wallSpot", &wallSpot, &b_CalibReadout_CalibReadoutHeader_wallSpot);
   fChain->SetBranchAddress("inwardFacing", &inwardFacing, &b_CalibReadout_CalibReadoutHeader_inwardFacing);
/*
   fChain->SetBranchAddress("nHitsRpc", &nHitsRpc, &b_CalibReadout_CalibReadoutHeader_nHitsRpc);
   fChain->SetBranchAddress("rpcRow", &rpcRow, &b_CalibReadout_CalibReadoutHeader_rpcRow);
   fChain->SetBranchAddress("rpcColumn", &rpcColumn, &b_CalibReadout_CalibReadoutHeader_rpcColumn);
   fChain->SetBranchAddress("rpcLayer", &rpcLayer, &b_CalibReadout_CalibReadoutHeader_rpcLayer);
   fChain->SetBranchAddress("rpcStrip", &rpcStrip, &b_CalibReadout_CalibReadoutHeader_rpcStrip);
   fChain->SetBranchAddress("rpcFromRot", &rpcFromRot, &b_CalibReadout_CalibReadoutHeader_rpcFromRot);
*/
   Notify();
}

Bool_t CalibReadoutHeader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CalibReadoutHeader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CalibReadoutHeader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef CalibReadoutHeader_cxx
