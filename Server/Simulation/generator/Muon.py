#!/usr/bin/env python
from GaudiKernel import SystemOfUnits as units

def Muon(name='Muon',
         musicsite='DYB',
         muonvolumn='RPC',
         volume='/dd/Structure/Pool/db-ows',
         start_time=0,
         lifetime=10*units.s,
         prophet=True,
         seed=12345):
    '''
       configure Muon generator
    '''

    # set up Gnrtr itself
    from Gnrtr.GnrtrConf import Gnrtr
    gnrtr = Gnrtr(name)
    
    gnrtr.GenTools = [ "GtHepEvtGenTool/"+name+"Gen",
                       "GtPositionerTool/"+name+"Pos",
                       "GtTimeratorTool/"+name+"Tim",
                       "GtTransformTool/"+name+"Tra",
                       "MuonProphet/"+name+"Prophet"]
    
    gnrtr.TimeStamp = start_time

    # set up each tools
    from GenTools.GenToolsConf import GtPositionerTool, GtTransformTool, GtTimeratorTool, GtHepEvtGenTool

    # Set up Gen
    # Get cosmic muon path
    import os
    MuonDataPath = os.getenv('MuonDataPath')
    if MuonDataPath is None:
        print "Muon data path ($MuonDataPath) is not defined."
        import sys
        sys.exit()
    else:
        print "Read muon data from ",MuonDataPath
            
    # set the muon generator command line
    # Muon.exe -n 20000 -s DYB -v RPC -seed 1 -r Yes -music_dir ....../data/trunk/NewMuonGenerator/data"
    import time
    seed = int((time.time()-int(time.time()))*1000000)
    # print out muon command line    
    print "Muon.exe -n 1000000 -s %s -v %s -seed %s -r Yes -music_dir %s|"%(musicsite,muonvolumn,seed,MuonDataPath)
    hepEvtDataSource = "Muon.exe -n 1000000 -s %s -v %s -seed %s -r Yes -music_dir %s|"%(musicsite,muonvolumn,seed,MuonDataPath)
        
    exe = hepEvtDataSource.split(' ')[0]
    NAME = exe[exe.rfind('/')+1:]
    dot = NAME.rfind('.')
    baseNAME = NAME
    if dot > 0: baseNAME = NAME[:dot]
    sanitized = baseNAME.replace('.','_')
    
    # If we got an executable and it is relative, look for it in the path
    if hepEvtDataSource[-1] == '|' and hepEvtDataSource[0] != '/':
        import os.path
        path = os.getenv('PATH')
        for p in path:
            if (os.path.isfile(path+'/'+exe)):
                hepEvtDataSource = path+'/'+exe + ' ' + ' '.join(hepEvtDataSource.split(' ')[1:])
                break
            continue
        pass
        
    #generator
    # gen=GtHepEvtGenTool(name+'Gen',HepEvtDataSource = hepEvtDataSource)
    gen=GtHepEvtGenTool(name+'Gen',HepEvtDataSource = "/data5/wangzhe/zlab/Production/muonEvt.txt")
    #gen.OutputLevel = 2
    gen.HepEvtDataSource = hepEvtDataSource
    
    # Set up positioner
    pos=GtPositionerTool(name+'Pos',Volume=volume)
    pos.Mode = "Relative"
    pos.Position = [0,0,0]

    # Set up timerator
    tim=GtTimeratorTool(name+'Tim')
    tim.LifeTime = lifetime
    
    # transform
    tra=GtTransformTool(name+'Tra',Volume=volume)
    tra.Offset = [0., 0., (0.042)*units.meter]

    ## More surprise from muon starts from here.
    from MuonProphet.MuonProphetConf import MuonProphet
    prophet=MuonProphet( name+"Prophet" );
    # The can completely turn the tool off.
    prophet.Active = prophet
    prophet.Site = "DayaBay"
    # Note that the number of parameters of
    # Tools, Yields, YieldMeasuredAt and Lifetimes must be the same.
    prophet.GenTools           = [ "Li9He8Decayerator/Li9He8" ]
    prophet.GenYields          = [ 3.86e-7*units.cm2/units.gram ]
    prophet.GenYieldMeasuredAt = [ 260*units.GeV ]
    prophet.GenLifetimes       = [ 0.178*units.s ]

    # trigger related configuration
    prophet.TrkLengthInWaterThres = 20*units.cm
    prophet.WaterPoolTriggerEff = 0.9999
    #prophet.OutputLevel=2 

    # Set false, otherwise all times will be reset so the signal vertex is at t=0.
    from G4DataHelpers.G4DataHelpersConf import HepMCtoG4
    convertor = HepMCtoG4()
    convertor.ZeroTime = False
                            
    
    return gnrtr

if __name__ == "__main__":
    obj=Muon()
    
