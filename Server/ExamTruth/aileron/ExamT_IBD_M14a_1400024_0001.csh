#!/bin/tcsh 
source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-trunk/nuwa-opt.tcsh
setenv CMTPROJECTPATH $CMTPROJECTPATH\:/dybfs/users/beizhenhu/mywork/
source /dybfs/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/cmt/setup.csh
source /dybfs/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/cmt/setup.csh
cd /dybfs/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/aileron
nuwa.py -A 0.0 -n -1 -m "run -o out.root" /dybfs/mc/M14A/IBD/recon.Neutrino.1400022.Physics.EH1-AD1.M14A-I._0001.root > ibd_2019027_r001.log 
 
