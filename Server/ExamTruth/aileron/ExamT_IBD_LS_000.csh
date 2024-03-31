#!/bin/tcsh 
source /afs/ihep.ac.cn/soft/dayabay/NuWa-64/env/NuWa-3.10.1/nuwa-opt.tcsh
setenv CMTPROJECTPATH $CMTPROJECTPATH\:/publicfs/dyb/data/userdata/beizhenhu/mywork 
source /publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Analysis/forM14a/ExamTruth/cmt/setup.csh 
source /publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Analysis/forM14a/ExamTruth/cmt/setup.csh 
cd /publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Analysis/forM14a/ExamTruth/aileron
nuwa.py -A 0.0 -n -1 -m "run -o testResults.root" /publicfs/dyb/data/mc/M14A/IBD/recon.Neutrino.1400024.Physics.EH1-AD1.M14A-I._0217.root > test.log 
 
