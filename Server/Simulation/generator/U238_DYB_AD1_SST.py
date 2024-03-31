#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'U238_DYB_AD1_SST',
                        volume     = '/dd/Structure/AD/db-ade1',
                        nuclide    = 'U238',
                        abundance  = 4.65e18,
                        strategy   = 'Material',
                        material   = 'StainlessSteel',
                        )
    
    return radioact
