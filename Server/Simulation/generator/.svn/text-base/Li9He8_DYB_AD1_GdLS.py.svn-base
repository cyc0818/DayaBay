#!/usr/bin/env python
import GaudiKernel.SystemOfUnits as units
def GetGnrtr():
    from Gnrtr.Li9He8 import Li9He8
    # from IBD import EvtGenerator
    li9he8 = Li9He8(name     = 'Li9He8_DYB_AD1_GdLS',
                    volume   = '/dd/Structure/AD/db-oil1',
                    strategy = 'Material',
                    material = 'GdDopedLS',
                    mode     = 'Uniform',
                    Li9Fraction = 0.9,
                    CompleteDecay = True,
                    Lifetime = 10*units.second
                    )
    
    return li9he8
