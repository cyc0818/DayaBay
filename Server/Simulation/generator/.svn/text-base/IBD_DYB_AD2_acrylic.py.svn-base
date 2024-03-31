#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.IBD import EvtGenerator
    # from IBD import EvtGenerator
    ibd = EvtGenerator(name     = 'IBD_DYB_AD2_acrylic',
                       seed     = 1965,
                       volume   = '/dd/Structure/AD/db-oil2',
                       strategy = 'Material',
                       material = 'Acrylic',
                       mode     = 'Uniform',
                       lifetime = 901.6*units.second   #daya bay site
                       )
    
    return ibd
