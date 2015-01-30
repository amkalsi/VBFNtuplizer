import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
#process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.load("PhysicsTools.PatAlgos.slimming.slimming_cff")
#process.load("PhysicsTools.PatAlgos.slimming.pileupJetId_cfi")
#from RecoJets.JetProducers.AnomalousCellParameters_cfi import *
#from RecoJets.JetProducers.PFJetParameters_cfi import *

#process.options.allowUnscheduled = cms.untracked.bool(True)
#process.GlobalTag.globaltag = 'PLS170_V7AN1::All'
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    'root://xrootd.unl.edu//store/mc/Spring14miniaod/DYJetsToLL_M-50_13TeV-madgraph-pythia8-tauola_v2/MINIAODSIM/PU20bx25_POSTLS170_V5-v1/00000/00245653-EC23-E411-B9BF-02163E006C73.root'
     'root://xrootd.unl.edu//store/mc/Phys14DR/DYToMuMu_M-50_Tune4C_13TeV-pythia8/MINIAODSIM/PU40bx25_tsg_castor_PHYS14_25_V1-v2/00000/622CAFBA-BD9A-E411-BE11-002481E14FFC.root'
    )
)

process.TFileService = cms.Service("TFileService",
fileName = cms.string("OutTree.root")
)

process.demo = cms.EDAnalyzer("TauAnalyzerMini",
    debug_ = cms.bool(True),
    fillmuoninfo = cms.bool(True),
    filltauinfo = cms.bool(True),
    fillgeninfo = cms.bool(True),
    fillPVinfo  = cms.bool(True),
    filljetinfo = cms.bool(True),
    fillMETinfo = cms.bool(True),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    muons = cms.InputTag("slimmedMuons"),
    electrons = cms.InputTag("slimmedElectrons"),
    taus = cms.InputTag("slimmedTaus"),
    photons = cms.InputTag("slimmedPhotons"),
    jets = cms.InputTag("slimmedJets"),
    fatjets = cms.InputTag("slimmedJetsAK8"),
    mets = cms.InputTag("slimmedMETs"),
    bits = cms.InputTag("TriggerResults","","HLT"),
    prescales = cms.InputTag("patTrigger"),
    objects = cms.InputTag("selectedPatTrigger"),  
)


process.p = cms.Path(process.demo)
