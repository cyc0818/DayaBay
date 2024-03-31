#!/usr/bin/env python
from GaudiKernel import SystemOfUnits as units

def MuonGun(name='Muon',
            volume='/dd/Structure/Pool/db-ows',
            start_time=0,
            lifetime=10*units.s):
    '''
    configure Muon generator
    '''

    # set up Gnrtr itself
    from Gnrtr.GnrtrConf import Gnrtr
    gnrtr = Gnrtr(name);
    
    gnrtr.GenTools = [ "GtGunGenTool/"+name+"GunGen",
                       "GtPositionerTool/"+name+"Pos",
                       "GtTimeratorTool/"+name+"Tim",
                       "GtTransformTool/"+name+"Tra"
                       #,"MuonProphet/"+name+"Prophet"
                       ]

    gnrtr.TimeStamp = start_time

    # set up each tools
    from GaudiKernel import SystemOfUnits as units
    from GenTools.GenToolsConf import GtGunGenTool,GtPositionerTool, GtTransformTool, GtTimeratorTool, GtHepEvtGenTool
    from MuonProphet.MuonProphetConf import MuonProphet
    # Set up Gen
    gun = GtGunGenTool(name+"GunGen",
                       ParticlesPerEvent = 1,
                       ParticleName = "mu+",
                       Momentum = 5*units.GeV,
                       MomentumMode = "Fixed",
                       MomentumSpread = 4*units.MeV,
                       DirectionMode = "Fixed",
                       Direction = [ 0, 0, -1 ],
                       DirectionSpread = 3)
    
    # Set up positioner
    pos=GtPositionerTool(name+'Pos',Volume=volume)
    # I should use relateiv
    #pos.Mode = "Relative"
    pos.Mode = "Fixed"
    pos.Position = [1*units.meter,
                    1*units.meter,
                    10*units.meter]
    
    # Set up timerator
    tim=GtTimeratorTool(name+'Tim')
    tim.LifeTime = lifetime
    
    # transform
    tra=GtTransformTool(name+'Tra',Volume=volume)
    tra.Offset = [0., 0., (0.042)*units.meter]
    
    ## More surprise from muon starts from here.
    # muon prophet
    prophet=MuonProphet();
    #prophet.Active=False;        
    prophet.Site = "DayaBay"
    prophet.GenTools     = [ "Li9He8Decayerator/Li9He8" ]
    prophet.GenYields    = [ 0.5*units.cm2/units.gram ]
    prophet.GenYieldMeasuredAt = [260*units.GeV]
    prophet.GenLifetimes = [ 0.002*units.s ]
    
    # trigger related configuration
    prophet.TrkLengthInWaterThres = 20*units.cm
    prophet.WaterPoolTriggerEff = 0.9999
    
    # Set false, otherwise all times will be reset so the signal vertex is at t=0.
    from G4DataHelpers.G4DataHelpersConf import HepMCtoG4
    convertor = HepMCtoG4()
    convertor.ZeroTime = False
    
    return gnrtr

if __name__ == "__main__":
    obj=MuonGun()


    
