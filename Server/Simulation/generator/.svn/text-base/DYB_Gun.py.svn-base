#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gun import Gun
    gun = Gun( name='DYB_Gun',
               volume='/dd/Structure/AD/db-oil1',
               strategy = 'Material',
               material = 'LiquidScintillator',
               mode     = 'Uniform',
               start_time=0,
               particle="e+",
               lifetime=0.5*units.second
               )
    return gun
