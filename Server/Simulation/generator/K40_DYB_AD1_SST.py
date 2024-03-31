#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'K40_DYB_AD1_SST',
                        volume     = '/dd/Structure/AD/db-ade1',
                        nuclide    = 'K40',
                        abundance  = 1.44e19,
                        strategy   = 'Material',
                        material   = 'StainlessSteel',
                        )
    
    return radioact
