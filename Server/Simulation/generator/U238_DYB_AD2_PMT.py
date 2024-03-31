#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Radioact import Radioact
    # from Radioact import Radioact
    radioact = Radioact(name       = 'U238_DYB_AD2_PMT',
                        volume     = '/dd/Structure/AD/db-oil2',
                        nuclide    = 'U238',
                        abundance  = 6.45e19,
                        strategy   = 'VolumeType',
                        fillvolumes= 'lvPmtHemiVacuum'
                        )
    
    return radioact
