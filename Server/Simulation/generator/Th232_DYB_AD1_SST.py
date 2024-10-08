#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'Th232_DYB_AD1_SST',
                        volume     = '/dd/Structure/AD/db-ade1',
                        nuclide    = 'Th232',
                        abundance  = 7.22e19,
                        strategy   = 'Material',
                        material   = 'StainlessSteel',
                        )
    
    return radioact
