#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.IBD import EvtGenerator
    # from IBD import EvtGenerator
    ibd = EvtGenerator(name     = 'IBD_DYB_IWS',
                       seed     = 1965,
                       volume   = '/dd/Structure/Sites/db-rock',
                       strategy = 'Material',
                       material = 'IwsWater',
                       mode     = 'Uniform',
                       lifetime = 10*units.second   #daya bay site
                       )
    
    return ibd
