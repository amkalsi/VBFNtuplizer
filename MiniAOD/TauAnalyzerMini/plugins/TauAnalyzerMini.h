// -*- C++ -*-
//
// Package:    MiniAOD/TauAnalyzerMini
// Class:      TauAnalyzerMini
// 
/**\class TauAnalyzerMini TauAnalyzerMini.cc MiniAOD/TauAnalyzerMini/plugins/TauAnalyzerMini.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  kaur amandeepkalsi
//         Created:  Mon, 03 Nov 2014 18:22:03 GMT
//
//

#ifndef  TREE_MAKER_H                                                                                                                                    
#define  TREE_MAKER_H


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "MuonSelector.h"
#include "TauSelector.h"
#include "JetSelector.h"
#include "PVSelector.h"
#include "GenParticleSelector.h"
#include "METSelector.h"

#ifdef __MAKECINT__
#pragma link C++ class std::vector<std::vector<int> >+;
#pragma link C++ class std::vector<std::vector<std::string> >+;
#pragma link C++ class std::vector<std::vector<TString> >+;
#pragma link C++ class std::vector<std::vector<float> >+;
#pragma link C++ class std::vector<std::vector<double> >+;
#pragma link C++ class std::vector<std::vector<bool> >+;
#pragma extra_include "std::vector";
#endif
//
// class declaration
//

class TauAnalyzerMini : public edm::EDAnalyzer {
public:
  explicit TauAnalyzerMini(const edm::ParameterSet&);
  ~TauAnalyzerMini();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  void clearvectors();
  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  
  // ----------member data ---------------------------
  
  TFile* file;
  TTree* tree_;
  const size_t MaxN;
  bool debug_;
  
  bool fillmuoninfo;
  bool filltauinfo;
  bool filljetinfo;
  bool fillgeninfo;
  bool fillPVinfo;
  bool fillMETinfo;

  MuonSelector *muselector ;
  TauSelector *tauselector;
  JetSelector *jetselector;
  GenParticleSelector *genselector;
  PVSelector *pvselector;
  METSelector *metselector;
};

#endif 
  
  
