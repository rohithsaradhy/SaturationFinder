import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

import os,sys


# Make sure you change the name of the electronics map....
# dataFolder ="/eos/cms/store/group/dpg_hgcal/tb_hgcal/october2017_h6/HGCalTBSkiroc2CMS"
dataFolder = "/eos/cms/store/group/dpg_hgcal/tb_hgcal/october2017/HGCalTBSkiroc2CMS"
# dataFolder = "/eos/cms/store/group/dpg_hgcal/tb_hgcal/july2017/HGCalTBSkiroc2CMS"
noiseFolder="/eos/cms/store/group/dpg_hgcal/tb_hgcal/october2017/pedestalFiles/"
# noiseFolder="/eos/cms/store/group/dpg_hgcal/tb_hgcal/july2017/pedestalFiles/"
# noiseFolder="/eos/cms/store/group/dpg_hgcal/tb_hgcal/october2017_h6/pedestalFiles"



# Electronic Map to be used....
e_Map = "HGCal/CondObjects/data/map_CERN_Hexaboard_September_17Sensors_7EELayers_10FHLayers_V1.txt"
# e_Map = "HGCal/CondObjects/data/map_CERN_Hexaboard_October_20Sensors_5EELayers_7FHLayers_V1.txt"


options = VarParsing.VarParsing('standard') # avoid the options: maxEvents, files, secondaryFiles, output, secondaryOutput because they are already defined in 'standard'
#Change the data folder appropriately to where you wish to access the files from:
options.register('dataFolder',
                 dataFolder,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 'folder containing raw input')

options.register('runNumber',
                 106,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 'Input run to process')

options.register('outputFolder',
                 './Output/H2',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 'Output folder where analysis output are stored')

options.register('electronicMap',
                 e_Map,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 'path to the electronic map')



options.maxEvents =  -1
options.output ="cmsswEvents.root"

options.parseArguments()
# options.output = options.outputFolder+"/cmsswEvents_Run"+str(options.runNumber)+".root"
print options
if not os.path.isdir(options.dataFolder):
    sys.exit("Error: Data folder not found or inaccessible!")

# electronicMap="HGCal/CondObjects/data/map_CERN_Hexaboard_July_6Layers.txt"
# electronicMap="HGCal/Rajdeep_EMap.txt"
pedestalHighGain=noiseFolder+"/pedestalHG_"+str(options.runNumber)+".txt"
pedestalLowGain=noiseFolder+"/pedestalLG_"+str(options.runNumber)+".txt"
noisyChannels=noiseFolder+"/noisyChannels_"+str(options.runNumber)+".txt"

################################
process = cms.Process("rawhitprod")
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

####################################

process.source = cms.Source("PoolSource",
                            fileNames=cms.untracked.vstring("file:%s/cmsswEvents_Run%d.root"%(options.dataFolder,options.runNumber))
)

filename = options.outputFolder+"/HexaOutput_"+str(options.runNumber)+".root"
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(filename)
)


process.output = cms.OutputModule("PoolOutputModule",
                                  fileName = cms.untracked.string(options.output),
                                  outputCommands = cms.untracked.vstring('drop *',
                                                                         'keep *_*_HGCALTBRAWHITS_*')
)

process.rawhitproducer = cms.EDProducer("HGCalTBRawHitProducer",
                                        InputCollection=cms.InputTag("source","skiroc2cmsdata"),
                                        OutputCollectionName=cms.string("HGCALTBRAWHITS"),
                                        ElectronicMap=cms.untracked.string(options.electronicMap),
                                        SubtractPedestal=cms.untracked.bool(True),
                                        MaskNoisyChannels=cms.untracked.bool(True),
                                        HighGainPedestalFileName=cms.untracked.string(pedestalHighGain),
                                        LowGainPedestalFileName=cms.untracked.string(pedestalLowGain),
                                        ChannelsToMaskFileName=cms.untracked.string(noisyChannels)
)

process.rawhitplotter = cms.EDAnalyzer("HightoLow",
                                       InputCollection=cms.InputTag("rawhitproducer","HGCALTBRAWHITS"),
                                       ElectronicMap=cms.untracked.string(options.electronicMap),
                                       SensorSize=cms.untracked.int32(128),
                                       EventPlotter=cms.untracked.bool(True),
                                       SubtractCommonMode=cms.untracked.bool(True)
)

process.pulseshapeplotter = cms.EDAnalyzer("NTuplizer",
                                           InputCollection=cms.InputTag("rawhitproducer","HGCALTBRAWHITS"),
                                           ElectronicMap=cms.untracked.string(options.electronicMap)
)


process.p = cms.Path( process.rawhitproducer*process.pulseshapeplotter )#*process.pulseshapeplotter )

process.end = cms.EndPath(process.output)
