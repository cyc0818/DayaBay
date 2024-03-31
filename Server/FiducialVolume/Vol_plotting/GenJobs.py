#!/usr/bin/env python


import sys,os
if __name__ == "__main__":

    nowDir = os.getcwd()
    site = "EH2"
    DataList = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/EvtSelect/"
    AppDir = "/dybfs2/users/yuchincheng/workdir/IBD/code/FiducialVolume/Cell_plotting"
    OutputDir = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/"+site+"/Plots/"
    scriptDir = nowDir+"/bashFile/"+site+"/"

    ListOfList = os.listdir( DataList )
    for run in ListOfList:
        listName = run.split('.')[0]+".list"
        runNo = run.split('.')[0][4:9]
        print runNo
	FILE0 = open(scriptDir+listName,"w")
        FILE0.writelines(DataList+run+" \n")
	FILE0.close()
        base = "IBD_p17b_"+runNo
        cshfile = scriptDir+base+".sh"
        FILE = open(cshfile,"w")
        FILE.writelines("#!/bin/bash \n")
        FILE.writelines("cd "+AppDir+" \n")
        FILE.writelines("./main "+scriptDir+listName+" "+OutputDir+base+".root \n")
        FILE.close()
        os.system("chmod a+x "+cshfile)
        os.system( "/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin/hep_sub -os CentOS7 -mem 5000 "+cshfile )
