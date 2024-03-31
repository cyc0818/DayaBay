#!/usr/bin/env python


import sys,os
if __name__ == "__main__":

    nowDir = os.getcwd()
    site = "EH1"
    #NuWa version: 3.14.2 
    p17bv3 = "/dybfs/rec/P17B/GoodRun_v3/"+site+"/"
    p17b = "/dybfs/rec/P17B/goodrunlist_p17b_v4/good_v4_sync.ihep/"+site+"/"
    p19a = "/dybfs/rec/P19A/goodrunlist_p19a_v5/good_v5_sync.ihep/"+site+"/"
    p20a = "/dybfs/rec/P20A/goodrunlist_p20a_v3/good_v3_sync.ihep/"+site+"/"
    p21a = "/dybfs/rec/P21A/goodrunlist_p21a_v1/good_v1_sync.ihep/"+site+"/"

    AppDir1 = "/dybfs2/users/yuchincheng/workdir/IBD/code/PreCuts"
    OutputDir1 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/PreCuts/"
    AppDir2 = "/dybfs2/users/yuchincheng/workdir/IBD/code/EvtSelect"
    OutputDir2 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/Pairs/"
    AppDir2 = "/dybfs2/users/yuchincheng/workdir/IBD/code/plotting"
    OutputDir2 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/Plots/"
    #
    scriptDir = nowDir+"/tcshFile/"+site+"/"

    ListOfList = os.listdir( p17bv3 )
    for run in ListOfList:
        listName = run.split('.')[0]
        runNo = run.split('.')[0][3:8]
        print runNo
        base1 = "PreCut_"+runNo
        base2 = "Evt_"+runNo
        base3 = "PreCut_"+runNo
        cshfile = scriptDir+base+".csh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("echo \"${_CONDOR_IHEP_REMOTE_HOST}\" \n")
        FILE.writelines("cd "+AppDir1+" \n")
        FILE.writelines("source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh \n")
        #FILE.writelines("source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-trunk/nuwa-opt.tcsh \n")
        FILE.writelines("./main "+p17bv3+listName+".list "+OutputDir1+base1+".root \n")
        FILE.writelines("cd "+AppDir2+" \n")
        FILE.close()
        #base2 = "job_"+runNo
        #jobfile = scriptDir+base2+".csh"
        #FILE = open(jobfile,"w")
        #FILE.writelines("/cvmfs/container.ihep.ac.cn/bin/hep_container exec SL6 -g dyw tcsh "+cshfile)
        #FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -mem 4000 "+cshfile)
        #os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -g dyw -os SL6 -wt mid "+cshfile)
        #os.system("chmod a+x "+jobfile)
        #os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -mem 4000 "+jobfile)
