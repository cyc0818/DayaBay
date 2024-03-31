#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'K40_DYB_AD1_GdLS',
                        volume     = '/dd/Structure/AD/db-oil1',
                        nuclide    = 'K40',
                        abundance  = 3.01e17,
                        strategy   = 'Material',
                        material   = 'GdDopedLS',
                        )
    
    return radioact
