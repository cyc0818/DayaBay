#!/usr/bin/env python

import sys,os
if __name__ == "__main__":

    NowDir = os.getcwd()
    area = "FullVolume"
    nuwaPath = "/afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh"
    #mcDataPath = "/dybfs2/users/lijj16/ShareMC/NuwaFullChain/Production/normal/tot/"
    mcDataPath  = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/myProduction/"
    dataPath  = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/nKE_tree/"
    scriptDir = NowDir+"/Script/"

    #os.chdir(dataPath);
    for runNo in range(165001,200001):
        sourceFile = "recon_FullVolume_"+str(runNo).zfill(4)
        outputFile = "prompteff_"+str(runNo).zfill(4)
        cshfile = scriptDir+outputFile+".csh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("source "+nuwaPath+"\n")
        FILE.writelines("source /dybfs2/users/yuchincheng/workdir/IBD/code/MyPromptEfficiencyAlg/cmt/setup.csh \n")
        FILE.writelines("cd "+NowDir+"\n")
        FILE.writelines("nuwa.py -A 250 -n -1 -m \"efficiency -o "+dataPath+outputFile+".root\" "+mcDataPath+sourceFile+".root> "+dataPath+"ibd_"+area+"_r"+str(runNo)+".log \n ")
        FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -os SL6 "+cshfile+" -g dyw" )
        #os.system("qsub -q dyb64q "+outputFile+".csh")


        #/dybfs2/users/yuchincheng/workdir/IBD/data/ExamTruth/aileron
        #/dybfs2/users/lijj16/ShareMC/NuwaFullChain/Production/normal/tot
