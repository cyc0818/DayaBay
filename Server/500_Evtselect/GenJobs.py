#!/usr/bin/env python


import sys,os
if __name__ == "__main__":

    nowDir = os.getcwd()
    site = "EH1"
    DataList = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/PreCuts/"
    AppDir = "/dybfs2/users/yuchincheng/workdir/IBD/code/500_Evtselect"
    OutputDir = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/EvtSelect/"
    scriptDir = nowDir+"/tcshFile/"+site+"/"

    ListOfList = os.listdir( DataList )
    for run in ListOfList:
        listName = run.split('.')[0]+".list"
        runNo = run.split('.')[0][7:12]
        print run
	FILE0 = open(scriptDir+listName,"w")
        FILE0.writelines(DataList+run+" \n")
	FILE0.close()
        base = "Evt_"+runNo
        cshfile = scriptDir+base+".csh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/tcsh \n")
        FILE.writelines("cd "+AppDir+" \n")
        FILE.writelines("source /afs/ihep.ac.cn/soft/dayabay/NuWa-slc6/env/NuWa-3.14.0/nuwa-opt.tcsh \n")
        FILE.writelines("./main "+scriptDir+listName+" "+OutputDir+base+".root \n")
        FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -os SL6 -mem 4500 "+cshfile )
