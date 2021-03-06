import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

import os,sys

options = VarParsing.VarParsing('standard') # avoid the options: maxEvents, files, secondaryFiles, output, secondaryOutput because they are already defined in 'standard'
#Change the data folder appropriately to where you wish to access the files from:
options.register('dataFolder',
                 '/eos/cms/store/group/dpg_hgcal/tb_hgcal/october2017_h6/October2017_TB_data_orm',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 'folder containing raw input')

options.register('runNumber',
                 106,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 'Input run to process')

options.register('outputFolder',
                 './Output',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 'Output folder where analysis output are stored')

options.register('dataFormat',
                 1,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 'Data formats int -> important for parameter setting')

options.register('electronicMap',
                 "HGCal/CondObjects/data/map_CERN_Hexaboard_October_20Sensors_5EELayers_7FHLayers_V1.txt",
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 'path to the electronic map')
#electronicMap="HGCal/CondObjects/data/map_CERN_Hexaboard_28Layers_AllFlipped.txt"
#electronicMap="HGCal/CondObjects/data/map_CERN_Hexaboard_July_6Layers.txt"
#electronicMap="HGCal/CondObjects/data/map_CERN_Hexaboard_September_17Sensors_7EELayers_10FHLayers_V1.txt" # end of september
#electronicMap="HGCal/CondObjects/data/map_CERN_Hexaboard_October_17Sensors_5EELayers_6FHLayers_V1.txt" # october 18-22, 1st conf
#electronicMap="HGCal/CondObjects/data/map_CERN_Hexaboard_October_20Sensors_5EELayers_7FHLayers_V1.txt" # october 18-22, 2nd conf

options.register('beamEnergy',
                0,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.float,
                 'Beam energy.'
                )

options.register('beamParticlePDGID',
                 0,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 'Beam particles PDG ID.'
                )

options.register('runType',
                 "Beam",
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 'Run type: Pedestal, Beam, Simulation.'
                )

options.register('setupConfiguration',
                4,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 'setupConfiguration (1: July - 4: 20 Layers in October in H6A".'
                )

options.maxEvents = -1
options.output = "cmsswEvents.root"

options.parseArguments()
print options
if not os.path.isdir(options.dataFolder):
    sys.exit("Error: Data folder not found or inaccessible!")

pedestalHighGain=options.outputFolder+"/pedestalHG_"+str(options.runNumber)+".txt"
pedestalLowGain=options.outputFolder+"/pedestalLG_"+str(options.runNumber)+".txt"
noisyChannels=options.outputFolder+"/noisyChannels_"+str(options.runNumber)+".txt"

################################
process = cms.Process("unpack")
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

####################################

if options.dataFormat==0 :
    numberOfBytesForTheHeader=8
    numberOfBytesForTheTrailer=4
    numberOfBytesForTheEventTrailers=4
elif options.dataFormat==1 :
    numberOfBytesForTheHeader=12
    numberOfBytesForTheTrailer=4
    numberOfBytesForTheEventTrailers=12
process.source = cms.Source("HGCalTBRawDataSource",
                            ElectronicMap=cms.untracked.string(options.electronicMap),
                            fileNames=cms.untracked.vstring("file:%s/HexaData_Run%04d.raw"%(options.dataFolder,options.runNumber)),
                            OutputCollectionName=cms.untracked.string("skiroc2cmsdata"),
                            NumberOf32BitsWordsPerReadOut=cms.untracked.uint32(30787),
                            NumberOfBytesForTheHeader=cms.untracked.uint32(numberOfBytesForTheHeader),
                            NumberOfBytesForTheTrailer=cms.untracked.uint32(numberOfBytesForTheTrailer),
                            NumberOfBytesForTheEventTrailers=cms.untracked.uint32(numberOfBytesForTheEventTrailers),
                            NSkipEvents=cms.untracked.uint32(0),
                            ReadTimeStamps=cms.untracked.bool(True),
                            DataFormats=cms.untracked.uint32(options.dataFormat),
                            timingFiles=cms.vstring("%s/HexaData_Run%04d_TIMING_RDOUT_ORM0.txt"%(options.dataFolder,options.runNumber),
                                                    "%s/HexaData_Run%04d_TIMING_RDOUT_ORM1.txt"%(options.dataFolder,options.runNumber),
                                                    "%s/HexaData_Run%04d_TIMING_RDOUT_ORM2.txt"%(options.dataFolder,options.runNumber)),
                            beamEnergy=cms.untracked.double(options.beamEnergy),
                            beamParticlePDGID=cms.untracked.int32(options.beamParticlePDGID),
                            runType=cms.untracked.string(options.runType),
                            setupConfiguration=cms.untracked.uint32(options.setupConfiguration)

)

filename = options.outputFolder+"/PedestalOutput_"+str(options.runNumber)+".root"
process.TFileService = cms.Service("TFileService", fileName=cms.string(filename))

process.output = cms.OutputModule("PoolOutputModule",
                                  fileName = cms.untracked.string(options.output)
)

process.content = cms.EDAnalyzer("EventContentAnalyzer") #add process.content in cms.Path if you want to check which collections are in the event

process.pedestalplotter = cms.EDAnalyzer("PedestalPlotter",
                                         SensorSize=cms.untracked.int32(128),
                                         WritePedestalFile=cms.untracked.bool(True),
                                         InputCollection=cms.InputTag("source","skiroc2cmsdata"),
                                         ElectronicMap=cms.untracked.string(options.electronicMap),
                                         HighGainPedestalFileName=cms.untracked.string(pedestalHighGain),
                                         LowGainPedestalFileName=cms.untracked.string(pedestalLowGain),
                                         WriteNoisyChannelsFile=cms.untracked.bool(True),
                                         NoisyChannelsFileName=cms.untracked.string(noisyChannels),
)

process.rawdataplotter = cms.EDAnalyzer("RawDataPlotter",
                                        SensorSize=cms.untracked.int32(128),
                                        EventPlotter=cms.untracked.bool(False),
                                        InputCollection=cms.InputTag("source","skiroc2cmsdata")
)

process.p = cms.Path( process.pedestalplotter )

process.end = cms.EndPath(process.output)
