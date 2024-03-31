#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Muon import Muon
    muon = Muon( name='Muon_DYB_RPC',
                 musicsite='DYB',
                 muonvolumn='RPC',
                 volume='/dd/Structure/Pool/db-ows',
                 start_time=0,
                 lifetime=0.001920*units.s,
                 prophet=True,
                 seed=12 )

    return muon
