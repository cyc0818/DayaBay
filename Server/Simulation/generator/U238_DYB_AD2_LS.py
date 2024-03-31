#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'U238_DYB_AD2_LS',
                        volume     = '/dd/Structure/AD/db-oil2',
                        nuclide    = 'U238',
                        abundance  = 5.43e16,
                        strategy   = 'Material',
                        material   = 'LiquidScintillator',
                        )
    
    return radioact
