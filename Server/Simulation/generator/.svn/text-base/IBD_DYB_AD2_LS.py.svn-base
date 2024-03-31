#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.IBD import EvtGenerator
    # from IBD import EvtGenerator
    ibd = EvtGenerator(name     = 'IBD_DYB_AD1_LS',
                       seed     = 1965,
                       volume   = '/dd/Structure/AD/db-oil2',
                       strategy = 'Material',
                       material = 'LiquidScintillator',
                       mode     = 'Uniform',
                       lifetime = 73.0*units.second   #daya bay site
                       )
    
    return ibd
