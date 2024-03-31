#!/bin/tcsh
#source /afs/ihep.ac.cn/soft/dayabay/NuWa-64/env/NuWa-trunk/nuwa-opt.tcsh
#source /afs/ihep.ac.cn/soft/dayabay/NuWa-64/env/NuWa-3.11.0/nuwa-opt.tcsh
source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-trunk/nuwa-opt.tcsh
setenv CMTPROJECTPATH $CMTPROJECTPATH\:/dybfs/users/beizhenhu/mywork
source /dybfs2/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/cmt/setup.csh
source /dybfs2/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/cmt/setup.csh
cd /dybfs2/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/aileron
nuwa.py -A 0.0 -n -1 -m "run -o /dybfs2/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/aileron/outTEST2.root" /dybfs/mc/M14A/IBD/recon.Neutrino.1400024.Physics.EH1-AD1.M14A-I._0216.root >log
