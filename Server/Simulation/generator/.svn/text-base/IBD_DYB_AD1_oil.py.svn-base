#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.IBD import EvtGenerator
    # from IBD import EvtGenerator
    ibd = EvtGenerator(name     = 'IBD_DYB_AD1_oil',
                       seed     = 1965,
                       volume   = '/dd/Structure/AD/db-ade1',
                       strategy = 'Material',
                       material = 'MineralOil',
                       mode     = 'Uniform',
                       lifetime = 36.3*units.second   #daya bay site
                       )
    
    return ibd
