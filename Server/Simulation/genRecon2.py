#!/usr/bin/env python
'''

  Mar.03. 2014
  Bei-Zhen Hu
'''
import sys,os
import time
import datetime

if __name__ == "__main__":

    events = 100
    binNum = "nominalLowThrd"
    area = "FullVolume"
    generator = "IBD_DYB_AD1_"+area
    Optional = "SingleLoader"   #Kinematic, Detector, Electronic, TrigRead or SingleLoader.
    #nuwaPath = "/afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-trunk/nuwa-opt.tcsh"
    nuwaPath = "/afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh"
    #nuwaPath = "/afs/ihep.ac.cn/soft/dayabay/NuWa-64/env/NuWa-3.11.0/nuwa-opt.tcsh"
    #myGenerator = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Generators/RadioActivity/Bi214/cmt/"
    #dataPath = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Production/data/Bi214Sim/"+binNum+"/"
    dataPath = "/dybfs2/users/beizhenhu/mywork/Simulation/Production/data/IBDsim/nominalLowThrd/"
    #dataPath = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Production/data/IBDsim/special/"
    simDir = "/dybfs2/users/beizhenhu/mywork/Simulation/Production/"
    os.chdir(dataPath)

    #FILE = open("bkRun.csh","w")
    for runNo in range(1000,1501):
	sourceFile = generator+"_"+binNum+"_NuWa3142_"+str(runNo).zfill(3) 
	outputFile = "recon_"+area+"_NuWa3142lowThrd_"+str(runNo).zfill(3)
        FILE = open(outputFile+".csh","w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("cd "+simDir+" \n")
        FILE.writelines("source "+nuwaPath+" \n")
        FILE.writelines("source "+nuwaPath+" \n")
        FILE.writelines("nuwa.py --history off --random off --repack-rpc=off -n -1 @$KUP11AROOT/share/runReco -o "+dataPath+outputFile+".root "+dataPath+sourceFile+".root > dataPath"+"recon_"+str(runNo)+".log  \n")
        FILE.close()
        os.system("chmod a+x "+outputFile+".csh")
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -os SL6 "+dataPath+outputFile+".csh " )
    #os.system("qsub -q dyb64q "+outputFile+".csh")	
