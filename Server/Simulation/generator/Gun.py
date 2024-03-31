#!/usr/bin/env python
from GaudiKernel import SystemOfUnits as units

def Gun(name='Gun',
        volume='/dd/Structure/AD/db-oil1',
        particle="e+",
	strategy = 'Material',
        material = 'LiquidScintillator',
        mode     = 'Uniform',
        start_time=0,
        lifetime=1.0*units.s):
    '''
    configure  generator
    '''

    # set up Gnrtr itself
    from Gnrtr.GnrtrConf import Gnrtr
    gnrtr = Gnrtr(name);
    
    gnrtr.GenTools = [ "GtGunGenTool/"+name+"GunGen",
                       "GtPositionerTool/"+name+"Pos",
                       "GtTimeratorTool/"+name+"Tim",
                       "GtTransformTool/"+name+"Tra"
                       ]

    gnrtr.TimeStamp = start_time

    # set up each tools
    from GaudiKernel import SystemOfUnits as units
    from GenTools.GenToolsConf import GtGunGenTool,GtPositionerTool, GtTransformTool, GtTimeratorTool, GtHepEvtGenTool

    # Set up Gen
    gun = GtGunGenTool(name+"GunGen",
                       ParticlesPerEvent = 1,
                       ParticleName = "e+",
                       Momentum = 2.089*units.MeV,
                       MomentumMode = "Fixed",
                       MomentumSpread = 0.0*units.MeV,
                       DirectionMode = "Uniform",
                       Direction = [ 0, 0, -1 ],
                       DirectionSpread = 3)
    
    # Set up positioner
    pos=GtPositionerTool(name+'Pos',Volume=volume)
    # I should use relateiv
    #pos.Mode = "Relative"
    pos.Mode = "Fixed"
    pos.Position = [0*units.meter,
                    0*units.meter,
                    0*units.meter]
    
    # Set up timerator
    tim=GtTimeratorTool(name+'Tim')
    tim.LifeTime = lifetime
    
    # transform
    tra=GtTransformTool(name+'Tra',Volume=volume)
    tra.Offset = [0., 0., (0.042)*units.meter]
    
    return gnrtr

if __name__ == "__main__":
    obj=Gun()
