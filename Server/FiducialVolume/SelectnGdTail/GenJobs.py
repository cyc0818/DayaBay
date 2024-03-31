#!/usr/bin/env python


import sys,os
if __name__ == "__main__":

    nowDir = os.getcwd()
    site = "EH2"
    DataList = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/EvtSelect/"
    AppDir = "/dybfs2/users/yuchincheng/workdir/IBD/code/FiducialVolume/SelectnGdTail"
    OutputDir = "/dybfs2/users/yuchincheng/workdir/IBD/data/nGdTail2/"+site+"/"
    scriptDir = nowDir+"/tcshFile/"+site+"/"

    ListOfList = os.listdir( DataList )
    for run in ListOfList:
        listName = run.split('.')[0]+".list"
        runNo = run.split('.')[0][4:9]
        print runNo
	FILE0 = open(scriptDir+listName,"w")
        FILE0.writelines(DataList+run+" \n")
	FILE0.close()
        base = "nGdtail_"+runNo
        cshfile = scriptDir+base+".csh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("cd "+AppDir+" \n")
        FILE.writelines("source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.2/nuwa-opt.tcsh \n")
        FILE.writelines("./main "+scriptDir+listName+" "+OutputDir+base+".root \n")
        FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -os SL6 -mem 4000 "+cshfile )
