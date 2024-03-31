#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units

def GetGnrtr():

    '''
    DayaBayAD1_ACU_A_Center_LED
    DayaBayAD1_ACU_B_GdlsEdge_LED
    DayaBayAD1_ACU_C_GammaCatcher_LED
    DayaBayAD1_AD_WallUpper_LED
    DayaBayAD1_AD_WallCenter_LED
    DayaBayAD1_AD_WallLower_LED

    '''

    name='LED'
    start_time=0.
    ledName='DayaBayAD1_ACU_C_GammaCatcher_LED' # 'DayaBayAD1_ACU_A_Center_LED',
    freq=500.0
    intensity=35000
    zpos=0.

    # setup up Gnrtr itself
    from Gnrtr.GnrtrConf import Gnrtr
    gnrtr = Gnrtr(name);
    
    # unique name for generator
    gnrtr.GenName = ledName 
    
    # configure GenTools for Sim15
    gnrtr.GenTools = [ "GtDiffuserBallTool/"+ledName+"ball",
                       "GtPositionerTool/"+ledName+"Positioner",
                       "GtTimeratorTool/"+ledName+"Timerator",
                       "GtTransformTool/"+ledName+"Transformer"
                       ]
    
    axis = 0
    xpos = 0.0
    ypos = 0.0

    # include variation in the number of photons per LED flash
    # This is set to 10% as a guess based on mini-dry run studies.
    intensityMode = "Gaus" # other options "Lorentz", "Fixed"
    intensitySpread = 350./3500. * float(intensity)
    ledFrequency = float(freq) * units.hertz
    pmtDataPath = None
    placeGeometry = True

    # next line makes photons only, diffuser ball geometry will be omitted
    placeGeometry = False
    if not placeGeometry :
        print "LED: Only make photons. Omit the diffuser ball geometry"
        
    detectorMap = {"DayaBayAD1":"/dd/Structure/AD/db-oil1",
                   "DayaBayAD2":"/dd/Structure/AD/db-oil2",
                   "LingAoAD1":"/dd/Structure/AD/la-oil1",
                   "LingAoAD2":"/dd/Structure/AD/la-oil2",
                   "FarAD1":"/dd/Structure/AD/far-oil1",
                   "FarAD2":"/dd/Structure/AD/far-oil2",
                   "FarAD3":"/dd/Structure/AD/far-oil3",
                   "FarAD4":"/dd/Structure/AD/far-oil4"
                   }

    # Get LED Source information
    from GaudiPython import gbl
    CalibSourceId = gbl.DayaBay.CalibSourceId
    ledId = CalibSourceId( ledName )
    xpos = ledId.nominalX()
    ypos = ledId.nominalY()
    volume = None
    if detectorMap.has_key( ledId.detName() ):
        # Set the correct coordinate system volume
        volume = detectorMap[ ledId.detName() ]
    else:
        print "ERROR: Unknown detector: ", ledId.detName()
        sys.exit(1)
        
    if ledId.isWallMounted():
        zpos = ledId.nominalZ()
        placeGeometry = False

    import GenTools
    from GenTools.Helpers import DiffuserBall
    ball = DiffuserBall( name=ledName,
                         useGeometry = placeGeometry )
    ball.setVolume( volume )
    ball.setPosition( [xpos, ypos, zpos] )
    ball.ball.PhotonsPerEvent = intensity
    ball.ball.PhotonsPerEventMode = intensityMode
    ball.ball.PhotonsPerEventSpread = intensitySpread
    ball.timerator.LifeTime = 1.0 / ledFrequency
    ball.timerator.Distribution = "Uniform" # periodic

    # Set run info
    from RunDataSvc.RunDataSvcConf import RunDataSvc
    runDataSvc = RunDataSvc()
    runDataSvc.SimRunType = "Calibration"
    runDataSvc.SimCalibSources = [ ledName ]
    runDataSvc.SimLedFrequency = { ledName : ledFrequency }
    runDataSvc.SimCalibZPosition = { ledName : zpos }    
    
    return gnrtr
