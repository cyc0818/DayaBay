#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'Th232_DYB_AD1_PMT',
                        volume     = '/dd/Structure/AD/db-oil1',
                        nuclide    = 'Th232',
                        abundance  = 1.28e20,
                        strategy   = 'VolumeType',
                        fillvolumes= 'lvPmtHemiVacuum'
                        )
    
    return radioact
