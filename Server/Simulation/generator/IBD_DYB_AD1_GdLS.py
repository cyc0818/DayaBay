#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.IBD import EvtGenerator
    # from IBD import EvtGenerator
    ibd = EvtGenerator(name     = 'IBD_DYB_AD1_GdLS',
                       seed     = 1965,
                       volume   = '/dd/Structure/AD/db-oil1',
                       strategy = 'Material',
                       material = 'GdDopedLS',
                       mode     = 'Uniform',
                       lifetime = 78.4*units.second   #daya bay site
                       )
    
    return ibd
