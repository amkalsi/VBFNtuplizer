#include "TauAnalyzerMini.h"
#include <memory>
#include <string>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

TauAnalyzerMini::TauAnalyzerMini(const edm::ParameterSet& iConfig):MaxN(200)

   //now do what ever initialization is needed
{
 
  debug_               = iConfig.getParameter<bool>("debug_");
  fillmuoninfo         = iConfig.getParameter<bool>("fillmuoninfo");
  filltauinfo          = iConfig.getParameter<bool>("filltauinfo");
  filljetinfo          = iConfig.getParameter<bool>("filljetinfo"); 
  fillgeninfo          = iConfig.getParameter<bool>("fillgeninfo"); 
  fillPVinfo           = iConfig.getParameter<bool>("fillPVinfo"); 
  fillMETinfo          = iConfig.getParameter<bool>("fillMETinfo");
  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("tree","tree");
  
  if( fillmuoninfo)   muselector = new MuonSelector("miniAOD", tree_, debug_, iConfig);
  if( filltauinfo)    tauselector = new TauSelector("miniAOD", tree_, debug_, iConfig);

  if( filljetinfo)    jetselector = new JetSelector("miniAOD", tree_, debug_, iConfig);

  if( fillgeninfo)    genselector = new GenParticleSelector("miniAOD", tree_, debug_, iConfig);

  if( fillPVinfo)    pvselector = new PVSelector("miniAOD", tree_, debug_, iConfig);
  if( fillMETinfo)    metselector = new METSelector("miniAOD", tree_, debug_, iConfig);

  
}


TauAnalyzerMini::~TauAnalyzerMini()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TauAnalyzerMini::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace pat;
  using namespace reco;
 
 //if( filleventInfo_)       eventInfo_      ->Fill(iEvent);

 if( fillmuoninfo)   muselector->Fill(iEvent);
 if( filltauinfo)   tauselector->Fill(iEvent); 
 if( filljetinfo)   jetselector->Fill(iEvent);
 if( fillgeninfo)   genselector->Fill(iEvent); 
 if( fillPVinfo)    pvselector->Fill(iEvent);
 if( fillMETinfo)    metselector->Fill(iEvent);

 // if( filltauinfo)   tauselector->Fill(iEvent); 


  /*
 edm::Handle<edm::TriggerResults> triggerBits;
 edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
 edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

 iEvent.getByToken(triggerBits_, triggerBits);
 iEvent.getByToken(triggerObjects_, triggerObjects);
 iEvent.getByToken(triggerPrescales_, triggerPrescales);

 //
 const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
 for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
      if(triggerBits->accept(i) == 1) {   
     PassTriggerName.push_back(names.triggerName(i)); 
     PassTriggerPrescale.push_back(triggerPrescales->getPrescaleForIndex(i));
}
 }

  */

/*
  for (pat::TriggerObjectStandAlone obj : *triggerObjects) { // note: not "const &" since we want to call unpackPathNames
        obj.unpackPathNames(names);
        std::cout << "\tTrigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl;
       
	std::cout << "\t   Collection: " << obj.collection() << std::endl;
	std::cout << "\t   Type IDs:   ";
	for (unsigned h = 0; h < obj.filterIds().size(); ++h) std::cout << " " << obj.filterIds()[h] ;
	std::cout << std::endl;
	std::cout << "\t   Filters:    ";
        for (unsigned h = 0; h < obj.filterLabels().size(); ++h) std::cout << " " << obj.filterLabels()[h];
	std::cout << std::endl;
	std::vector<std::string> pathNamesAll  = obj.pathNames(false);
	std::vector<std::string> pathNamesLast = obj.pathNames(true);
	std::cout << "\t   Paths (" << pathNamesAll.size()<<"/"<<pathNamesLast.size()<<"):    ";
        for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
	  bool isBoth = obj.hasPathName( pathNamesAll[h], true, true ); 
	  bool isL3   = obj.hasPathName( pathNamesAll[h], false, true ); 
	  bool isLF   = obj.hasPathName( pathNamesAll[h], true, false ); 
	  bool isNone = obj.hasPathName( pathNamesAll[h], false, false ); 
	  std::cout << "   " << pathNamesAll[h];
	  if (isBoth) std::cout << "(L,3)";
	  if (isL3 && !isBoth) std::cout << "(*,3)";
	  if (isLF && !isBoth) std::cout << "(L,*)";
	  if (isNone && !isBoth && !isL3 && !isLF) std::cout << "(*,*)";
        
	}
  }



*/

 tree_->Fill();
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TauAnalyzerMini::beginJob()
{
  
 
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauAnalyzerMini::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
TauAnalyzerMini::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
TauAnalyzerMini::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
TauAnalyzerMini::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
TauAnalyzerMini::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauAnalyzerMini::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauAnalyzerMini);
