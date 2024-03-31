#!/usr/bin/env python

import sys,os
if __name__ == "__main__":
    dataPeriod = "P17B"
    RunType = ""
    program = "main"

    site = "EH1"
    GoodRunList = "/dybfs/rec/P17B/goodrunlist_p17b_v4/good_v4_sync.ihep/"+site+"/"
    AppDir = "/dybfs2/users/yuchincheng/workdir/IBD/code/IBDSelect/"
    OutPutDir = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/IBDSelect/"
    scriptDir = AppDir+"tcshFile/"+site+"/"

    ListOfList = os.listdir( GoodRunList )
    for run in ListOfList:
        listName = run.split('.')[0]
        runNo = run.split('.')[0]
        print runNo
        base = "IBD_"+runNo
        cshfile = scriptDir+base+".tcsh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("echo \"${_CONDOR_IHEP_REMOTE_HOST}\" \n")
        FILE.writelines("rerun:\n")
        FILE.writelines("cd "+AppDir+" \n")
        FILE.writelines("source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh \n")
        FILE.writelines("./main "+GoodRunList+listName+".list "+OutPutDir+base+".root \n")
        FILE.writelines("if(\"$?\" == \"0\")then\n")
        FILE.writelines("\techo \"Let's do it\"\n")
        FILE.writelines("else\n")
        FILE.writelines("\techo \"Resource again\"\n")
        FILE.writelines("\tgoto rerun\n")
        FILE.writelines("fi")
        FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub "+cshfile+" -g dyw" )

    site = "EH2"
    GoodRunList = "/dybfs/rec/P17B/goodrunlist_p17b_v4/good_v4_sync.ihep/"+site+"/"
    OutPutDir = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/IBDSelect/"
    scriptDir = AppDir+"tcshFile/"+site+"/"
    ListOfList = os.listdir( GoodRunList )
    for run in ListOfList:
        listName = run.split('.')[0]
        runNo = run.split('.')[0]
        print runNo
        base = "IBD_"+runNo
        cshfile = scriptDir+base+".tcsh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("echo \"${_CONDOR_IHEP_REMOTE_HOST}\" \n")
        FILE.writelines("rerun:\n")
        FILE.writelines("cd "+AppDir+" \n")
        FILE.writelines("source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh \n")
        FILE.writelines("./main "+GoodRunList+listName+".list "+OutPutDir+base+".root \n")
        FILE.writelines("if(\"$?\" == \"0\")then\n")
        FILE.writelines("\techo \"Let's do it\"\n")
        FILE.writelines("else\n")
        FILE.writelines("\techo \"Resource again\"\n")
        FILE.writelines("\tgoto rerun\n")
        FILE.writelines("fi")
        FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub "+cshfile+" -g dyw" )

    site = "EH3"
    GoodRunList = "/dybfs/rec/P17B/goodrunlist_p17b_v4/good_v4_sync.ihep/"+site+"/"
    OutPutDir = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/IBDSelect/"
    scriptDir = AppDir+"tcshFile/"+site+"/"
    ListOfList = os.listdir( GoodRunList )
    for run in ListOfList:
        listName = run.split('.')[0]
        runNo = run.split('.')[0]
        print runNo
        base = "IBD_"+runNo
        cshfile = scriptDir+base+".tcsh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("echo \"${_CONDOR_IHEP_REMOTE_HOST}\" \n")
        FILE.writelines("rerun:\n")
        FILE.writelines("cd "+AppDir+" \n")
        FILE.writelines("source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh \n")
        FILE.writelines("./main "+GoodRunList+listName+".list "+OutPutDir+base+".root \n")
        FILE.writelines("if(\"$?\" == \"0\")then\n")
        FILE.writelines("\techo \"Let's do it\"\n")
        FILE.writelines("else\n")
        FILE.writelines("\techo \"Resource again\"\n")
        FILE.writelines("\tgoto rerun\n")
        FILE.writelines("fi")
        FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub "+cshfile+" -g dyw" )
