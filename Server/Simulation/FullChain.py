#!/usr/bin/env python
'''
Configure the full chain of simulation from kinematics to readouts to generate one type of event.

usage:
    nuwa.py -n50 -o fifteen.root -m "FullChain -g IBD_DYB_AD1_GdLS -T Detector" > log

    -g: A generator, for example IBD_DYB_AD1_GdLS is for IBD event in GdLS volume of AD1 of site DYB.
        IBD_DYB_AD1_GdLS must be a python module with a function of GetGnrtr returning a Gnrtr object.
        Remember to set your $PYTHONPATH.
        
    -T: Optional stages are: Kinematic, Detector, Electronic, TrigRead or SingleLoader.

    More options are available like -w: wall clock starting time
                                    -F: time format
                                    -s: seed for IBD generator

    Here is another example:
    nuwa.py -n50 -o fifteen.root -m "FullChain -g IBD_DYB_AD1_GdLS -T SingleLoader -w 2008-04-15T15:15:00 -s 1"
    
'''
import GaudiKernel.SystemOfUnits as units

class ConfigureFullChain:
    '''
    Configure a Full Chain of pull simulations.
    '''

    def __init__(self,argv):
        self.parse_args(argv)
        return

    def parse_args(self,argv):
        from optparse import OptionParser
        import time
        parser = OptionParser(usage=self.__doc__)
        default_time_format = '%Y-%m-%dT%H:%M:%S'
        parser.add_option("-w","--start-time",
                          help="Date string to set simulation start, assumed UTC",
                          default=time.strftime(default_time_format,time.localtime()))
        parser.add_option("-F","--time-format",
                          help="Format for parsing time (see man date), " \
                              + "default is '%s'"%default_time_format \
                              + " ('[YYYY]-[MM]-[DD]T[HH]:[MM]:[SS]')",
                          default=default_time_format)
        parser.add_option("-g","--generator",
                          help="A python module with a function of GetGnrtr returning a Gnrtr object.",
                          default="")
        parser.add_option("-T","--top-stage",
                          help="Kinematic, Detector, Electronic, TrigRead or SingleLoader",
                          default="SingleLoader")
        parser.add_option("-s","--seed",
                          help="Random seed for generators",
                          default=1234567)        

        (options,args) = parser.parse_args(args=argv)
        self.opts = options
        self.args = args

        # print "Your random seed =", self.opts.seed

        timeformat = self.opts.time_format
        print "Using time format =",timeformat

        try:
            datestring = self.opts.start_time
        except AttributeError:
            self.start_time_seconds = 0
        else:
            # This may raise ValueError if string and format don't
            # match.  Just let it get thrown.
            t = time.strptime(datestring,timeformat)
            self.start_time_seconds = time.mktime(t) - time.timezone
        print 'Start time in human readable format',self.opts.start_time 
        print 'Start time in seconds UTC =',self.start_time_seconds
        print 'Top stage =',self.opts.top_stage

        return

    def configureKinematic(self):

        print 'import %s'%self.opts.generator
        exec('import %s'%self.opts.generator)
        mod = eval(self.opts.generator)

        gnrtr = mod.GetGnrtr()
        gnrtr.TimeStamp = self.start_time_seconds          # overwrite the start time here
        gnrtr.ThisStageName = "Kinematic"
        self.stage_cfg.KinematicSequence.Members.append( gnrtr )
        
        return

    def configureDetector(self):
        '''Configure the Detector stage'''
        
        import DetSim
        ds = DetSim.Configure(physlist=DetSim.physics_list_basic+DetSim.physics_list_nuclear,site="dayabay",
                              use_push_algs = False)

        # QuantumEfficiency*CollectionEfficiency*QEScale = 0.24*1/0.9
        from DetSim.DetSimConf import DsPhysConsOptical
        optical = DsPhysConsOptical("GiGa.GiGaPhysListModular.DsPhysConsOptical")
        #optical.UseScintillation = False
        #optical.UseCerenkov = False
        # horn
        #optical.ScintPhotonScaleWeight = 3.5
        #optical.CerenPhotonScaleWeight = 3.5

        from DetSimProc.DetSimProcConf import DetSimProc
        dsp = DetSimProc()
        dsp.ThisStageName = "Detector"
        dsp.LowerStageName = "Kinematic"
        #dsp.OutputLevel = 2
        self.stage_cfg.DetectorSequence.Members.append(dsp)

        #ds.historian(trackSelection="all",vertexSelection="all")
        ds.historian(trackSelection="(pdg == 2112 or pdg ==22)",vertexSelection="(pdg == 2112 or pdg ==22)")
        params = {
            'start' :"(start > 0)",
            'track1':"(id==1)",
            'track2':"(id==2)",
            'inGdLS':"DetectorElementName == 'db-gds1'",
            'inLS':  "DetectorElementName == 'db-lso1'",
            'GD':    "MaterialName == '/dd/Materials/GdDopedLS'",
            'LS':    "MaterialName == '/dd/Materials/LiquidScintillator'",
            'MO':   "MaterialName == '/dd/Materials/MineralOil'",
            'IAV':   "DetectorElementName == 'db-iav1'",
            'OAV':   "DetectorElementName == 'db-oav1'",
            'IWS': "MaterialName == '/dd/Materials/IwsWater'",
            'OWS': "MaterialName == '/dd/Materials/OwsWater'",
            'lastvtx': "IsStopping == 1",
            'firstvtx': "IsStarting == 1",
            'NeutronTrk': "pdg == 2112",
            'NeutronMom': "creator == 2112",
            'NCap': "ProcessName == 'nCapture'",
            'Gamma': "pdg == 22",
            'Muon': "(pdg == 13 or pdg == -13)",
            "PositronRela": "ParentPdg == -11",
            "ElectronRela": "ParentPdg == 11",
            "NeutronRela":  "ParentPdg == 2112"
            }
        
        ds.unobserver(stats=[
                ["EDepInGdLS", "dE", "%(GD)s"%params],
                ["EDepInLS", "dE", "%(LS)s"%params],
                ["EDepInIAV", "dE", "%(IAV)s"%params],
                ["EDepInOAV", "dE", "%(OAV)s"%params],
                ["EDepInOIL", "dE", "%(MO)s"%params],
                
                ["QEPositron", "qdE", "%(PositronRela)s"%params],
                ["QEElectron", "qdE", "%(ElectronRela)s"%params],
                ["QENeutron",  "qdE", "%(NeutronRela)s"%params],

                ["QEDepInGdLS", "qdE", "%(GD)s"%params],
                ["QEDepInLS", "qdE", "%(LS)s"%params],
                ["QEDepInIAV", "qdE", "%(IAV)s"%params],
                ["QEDepInOAV", "qdE", "%(OAV)s"%params],
                ["QEDepInOIL", "qdE", "%(MO)s"%params],
                
                ["tQESumGdLS", "qEt", "%(GD)s"%params],
                ["xQESumGdLS", "qEx", "%(GD)s"%params],
                ["yQESumGdLS", "qEy", "%(GD)s"%params],
                ["zQESumGdLS", "qEz", "%(GD)s"%params],
                
                ["tQESumLS", "qEt", "%(LS)s"%params],
                ["xQESumLS", "qEx", "%(LS)s"%params],
                ["yQESumLS", "qEy", "%(LS)s"%params],
                ["zQESumLS", "qEz", "%(LS)s"%params],
                
                ["tQESumMO", "qEt", "%(MO)s"%params],
                ["xQESumMO", "qEx", "%(MO)s"%params],
                ["yQESumMO", "qEy", "%(MO)s"%params],
                ["zQESumMO", "qEz", "%(MO)s"%params],
                
                ["tCap",   "t","%(NCap)s and %(NeutronTrk)s"%params],
                ["xCap",   "x","%(NCap)s and %(NeutronTrk)s"%params],
                ["yCap",   "y","%(NCap)s and %(NeutronTrk)s"%params],
                ["zCap",   "z","%(NCap)s and %(NeutronTrk)s"%params],
 
                ["capTarget", "capTargetZ","%(NCap)s and %(NeutronTrk)s"%params],
                
                # track 1
                ["pdgId_Trk1","pdg","%(track1)s and %(start)s"%params],
                ["t_Trk1",    "t" , "%(track1)s and %(start)s"%params],
                ["x_Trk1",    "x", "%(track1)s and %(start)s"%params],
                ["y_Trk1",    "y", "%(track1)s and %(start)s"%params],
                ["z_Trk1",    "z", "%(track1)s and %(start)s"%params],
                ["tEnd_Trk1",    "t" , "%(track1)s and %(lastvtx)s"%params],
                ["xEnd_Trk1",    "x", "%(track1)s and %(lastvtx)s"%params],
                ["yEnd_Trk1",    "y", "%(track1)s and %(lastvtx)s"%params],
                ["zEnd_Trk1",    "z", "%(track1)s and %(lastvtx)s"%params],
                ["e_Trk1",    "E",  "%(track1)s and %(start)s"%params],
                ["p_Trk1",    "p",  "%(track1)s and %(start)s"%params],
                ["ke_Trk1",   "KE", "%(track1)s and %(start)s"%params],
                ["vx_Trk1",   "lvx","%(track1)s and %(start)s"%params],
                ["vy_Trk1",   "lvy","%(track1)s and %(start)s"%params],
                ["vz_Trk1",   "lvz","%(track1)s and %(start)s"%params],
                ["TrkLength_GD_Trk1",  "dx","%(track1)s and %(GD)s"%params],
                ["TrkLength_iAV_Trk1", "dx","%(track1)s and %(IAV)s"%params],
                ["TrkLength_LS_Trk1",  "dx","%(track1)s and %(LS)s"%params],
                ["TrkLength_oAV_Trk1", "dx","%(track1)s and %(OAV)s"%params],
                ["TrkLength_Oil_Trk1", "dx","%(track1)s and %(MO)s"%params],
                # track 2
                ["pdgId_Trk2","pdg","%(track2)s and %(start)s"%params],
                ["t_Trk2",    "t" , "%(track2)s and %(start)s"%params],
                ["x_Trk2",    "x", "%(track2)s and %(start)s"%params],
                ["y_Trk2",    "y", "%(track2)s and %(start)s"%params],
                ["z_Trk2",    "z", "%(track2)s and %(start)s"%params],
                ["tEnd_Trk2",    "t" , "%(track2)s and %(lastvtx)s"%params],
                ["xEnd_Trk2",    "x", "%(track2)s and %(lastvtx)s"%params],
                ["yEnd_Trk2",    "y", "%(track2)s and %(lastvtx)s"%params],
                ["zEnd_Trk2",    "z", "%(track2)s and %(lastvtx)s"%params],
                ["e_Trk2",    "E",  "%(track2)s and %(start)s"%params],
                ["p_Trk2",    "p",  "%(track2)s and %(start)s"%params],
                ["ke_Trk2",   "KE", "%(track2)s and %(start)s"%params],
                ["vx_Trk2",   "lvx","%(track2)s and %(start)s"%params],
                ["vy_Trk2",   "lvy","%(track2)s and %(start)s"%params],
                ["vz_Trk2",   "lvz","%(track2)s and %(start)s"%params],
                ["TrkLength_GD_Trk2",  "dx","%(track2)s and %(GD)s"%params],
                ["TrkLength_iAV_Trk2", "dx","%(track2)s and %(IAV)s"%params],
                ["TrkLength_LS_Trk2",  "dx","%(track2)s and %(LS)s"%params],
                ["TrkLength_oAV_Trk2", "dx","%(track2)s and %(OAV)s"%params],
                ["TrkLength_Oil_Trk2", "dx","%(track2)s and %(MO)s"%params]
                ])

        return

    def configureElectronic(self):
        '''Configure the Electronics stage'''

        import ElecSim
        es = ElecSim.Configure(use_push_algs = False)

        from ElecSimProc.ElecSimProcConf import ElecSimProc
        esp = ElecSimProc()
        esp.PmtTool = "EsPmtEffectPulseTool"
        esp.RpcTool = "EsIdealPulseTool"
        esp.FeeTool = "EsIdealFeeTool"
        esp.FecTool = "EsIdealFecTool"
        esp.Detectors = ["DayaBayAD1","DayaBayAD2","DayaBayIWS","DayaBayOWS"]

        esp.ThisStageName = "Electronic"
        esp.LowerStageName = "Detector"
        #esp.OutputLevel = 2
        self.stage_cfg.ElectronicSequence.Members.append(esp)
        return

    def configureTrigRead(self):
        '''Configure the Trigger and Readout stage'''
        from TrigReadProc.TrigReadProcConf import TrigReadProc
        tsp = TrigReadProc()
        tsp.ThisStageName = "TrigRead"
        tsp.LowerStageName = "Electronic"
        tsp.TrigTools = ["TsMultTriggerTool","TsESumTriggerTool"]
        '''
        import TrigSim.TrigSimConf as TsConf
        TsConf.TsMultTriggerTool().NHitTriggerThreshold = { "DayaBayAD1":191,
                                                            "DayaBayAD2":191,
                                                            "DayaBayIWS":191,
                                                            "DayaBayOWS":191 }
        
        TsConf.TsESumTriggerTool().UpperLowerThresholdMap = { "DayaBayAD1":2*units.volt,
                                                              "DayaBayAD2":2*units.volt,
                                                              "DayaBayIWS":2*units.volt,
                                                              "DayaBayOWS":2*units.volt }
        
        TsConf.TsESumTriggerTool().DigitalTotalThresholdMap = { "DayaBayAD1":0.02*units.volt,
                                                                "DayaBayAD2":0.02*units.volt,
                                                                "DayaBayIWS":0.02*units.volt,
                                                                "DayaBayOWS":0.02*units.volt }
        '''
        #tsp.RoTools = [...]
        #tsp.OutputLevel = 2
        self.stage_cfg.TrigReadSequence.Members.append(tsp)
        return

    def configureSingleLoader(self):
        '''Configure the SingleLoader stage'''
        from SingleLoader.SingleLoaderConf import SingleLoader
        sll = SingleLoader()
        sll.ThisStageName = "SingleLoader"
        sll.LowerStageName = "TrigRead"
        #sll.OutputLevel = 2
        self.stage_cfg.SingleLoaderSequence.Members.append(sll)

    def configureSim15(self):
        from Stage.StageConf import Sim15
        sim15=Sim15()
        sim15.TopStage=self.opts.top_stage
        sim15.TimeRange = 365*24*60*60*units.s

        from Gaudi.Configuration import ApplicationMgr
        theApp = ApplicationMgr()
        theApp.TopAlg.append(sim15)

    def configure(self):

        from Stage import Configure as StageConfigure
        self.stage_cfg = StageConfigure()

        stagedic={'Kinematic':1,'Detector':2,'Electronic':3,'TrigRead':4,'SingleLoader':5}

        if not self.opts.top_stage in stagedic:
            print 'Error, wrong top stage parameter', self.opts.top_stage
            print 'Valid stage is Kinematic, Detector, Electronic, TrigRead or SingleLoader'

        for stg,idx in stagedic.iteritems():
            if idx <= stagedic[self.opts.top_stage]:
                self.stage_cfg.addStages([stg])           ## stage tools are configured here.
                
        for stg in self.stage_cfg.stages:
            #self.stage_cfg.__dict__[stg].OutputLevel = 2
            pass

        if stagedic[self.opts.top_stage]>=1:
            self.configureKinematic()
        if stagedic[self.opts.top_stage]>=2:
            self.configureDetector()
        if stagedic[self.opts.top_stage]>=3:
            self.configureElectronic()
        if stagedic[self.opts.top_stage]>=4:
            self.configureTrigRead()
        if stagedic[self.opts.top_stage]>=5:
            self.configureSingleLoader()

        self.configureSim15()
        
        return
        
def configure(argv=[]):
    cfc = ConfigureFullChain(argv)
    cfc.configure()
    return

if __name__ == "__main__":
    import sys
    configure(sys.argv[1:])
    pass

