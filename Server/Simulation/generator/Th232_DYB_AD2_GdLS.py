#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'Th232_DYB_AD2_GdLS',
                        volume     = '/dd/Structure/AD/db-oil2',
                        nuclide    = 'Th232',
                        abundance  = 5.19e16,
                        strategy   = 'Material',
                        material   = 'GdDopedLS',
                        )
    
    return radioact
