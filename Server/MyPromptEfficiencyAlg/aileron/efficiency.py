#!/usr/bin/env python
#
#  -- Usage:
#     In this directory
#       >  nuwa.py -n 10 -m run
#     In other directories use MyPromptEfficiencyAlg.run
#       >  nuwa.py -n 10 -m"MyPromptEfficiencyAlg.efficiency -o outputname"  OptionalInput.root
#
import os
def configure(argv = []):
    import sys, getopt
    opts,args = getopt.getopt(argv,"o:")
    acuAxis = 'A'
    seed = 0
    for opt,arg in opts:
        if opt == "-o":
            output = arg
            print "======================================================"
            print "Name of the outpue file = ", output
            print "======================================================"
    from Gaudi.Configuration import ApplicationMgr
    theApp = ApplicationMgr()

    # Add myself into the queue
    from StatisticsSvc.StatisticsSvcConf import StatisticsSvc
    statssvc = StatisticsSvc()
    statssvc.Output = {"file1":output}

    from MyPromptEfficiencyAlg.MyPromptEfficiencyAlgConf import MyPromptEfficiencyAlg
    MyAlg=MyPromptEfficiencyAlg()
    theApp.TopAlg.append(MyAlg)
    return

def run(theApp):
    pass
