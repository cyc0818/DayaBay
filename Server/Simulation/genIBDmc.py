#!/usr/bin/env python
'''

  Mar.03. 2014
  Bei-Zhen Hu
'''
import sys,os
import time
import datetime

if __name__ == "__main__":

    events = 2000
    binNum = "nominalLowThrd"
    #area = "GdLS"
    area = "/dd/Structure/AD/db-oil1"
    generator = "FullVolume"
    Optional = "SingleLoader"   #Kinematic, Detector, Electronic, TrigRead or SingleLoader.
    #nuwaPath = "/afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-trunk/nuwa-opt.tcsh"
    nuwaPath = "/afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh"
    #nuwaPath = "/afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.11.0/nuwa-opt.tcsh"
    #myGenerator = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Generators/RadioActivity/Bi214/cmt/"
    #myGenerator = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Generators/RadioActivity/Special/"+binNum+"/Bi214/cmt/"
    #dataPath = "/dybfs2/users/beizhenhu/mywork/Simulation/Production/data/IBDsim/"+binNum+"/"
    #simDir = "/dybfs2/users/beizhenhu/mywork/Simulation/Production/"
    dataPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/myProduction/"
    simDir = "/dybfs2/users/yuchincheng/workdir/IBD/code/Simulation/"
    os.chdir(dataPath)

    for runNo in range(165001,200001):
	outputFile = generator+"_"+str(runNo).zfill(4)
	outputFile2 = "recon_"+generator+"_"+str(runNo).zfill(4)
	randomNum = 20000+runNo
	FILE = open(simDir+"tcshFile/"+outputFile+".csh","w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("cd "+simDir+" \n")
        FILE.writelines("source "+nuwaPath+" \n")
        FILE.writelines("source "+nuwaPath+" \n")
        FILE.writelines("nuwa.py -n "+str(events)+" -o "+dataPath+outputFile+".root -R "+str(randomNum)+" -m \"NewChain -T "+Optional+" -w 2012-04-15T15:15:00 -s "+str(randomNum)+" -v "+area+"\" > "+dataPath+outputFile+".log \n")
        FILE.writelines("nuwa.py --history off --random off --repack-rpc=off -n -1 @$KUP11AROOT/share/runReco -o "+dataPath+outputFile2+".root "+dataPath+outputFile+".root > "+dataPath+"recon_"+str(runNo)+".log  \n")
        FILE.writelines("rm -f "+dataPath+outputFile+".root \n")
        FILE.close()
    	os.system("chmod a+x "+simDir+"tcshFile/"+outputFile+".csh")
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -os SL6 -mem 4200 -prio 2 "+simDir+"tcshFile/"+outputFile+".csh " )
    	#os.system("chmod a+x "+outputFile+".csh")
        #os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub "+dataPath+outputFile+".csh -mem 5000 -g dyw" )
	#os.system("qsub -q dyb64q "+outputFile+".csh")	

