#include "JetSelector.h"

JetSelector::JetSelector(std::string name, TTree* tree, bool debug, const pset& iConfig):baseTree(name,tree,debug){
  
  SetBranches();
  jetToken_ = iConfig.getParameter<edm::InputTag>("jets");
  vertexInputTag = iConfig.getParameter<edm::InputTag>("vertices");
}

JetSelector::~JetSelector(){
  delete tree_;
}

void JetSelector::Fill(const edm::Event& iEvent){
  Clear();
  
  
  //  edm::Handle<edm::View<pat::Jet> > muon_h;
  // iEvent.getByLabel(muonToken_, muon_h);
  
  edm::Handle<reco::VertexCollection> vtx_h;
  iEvent.getByLabel(vertexInputTag, vtx_h);

  reco::VertexCollection::const_iterator firstGoodVertex = vtx_h->end();
  // require a good vertex 
  
  edm::Handle<pat::JetCollection> jets;                                       
  iEvent.getByLabel(jetToken_, jets);                                         
  
  sumpxForMht = 0.0; 
  sumpyForMht = 0.0;                                           
  sumptForHt  = 0.0;
  
  for (const pat::Jet &j : *jets) {
    sumpxForMht = sumpxForMht - j.px(); 
    sumpyForMht = sumpyForMht - j.py();            
    sumptForHt  = sumptForHt  + j.pt();
  }     
  
  
  for (const pat::Jet &j : *jets) { 
    if (j.pt() < 20) continue;
    JetPt.push_back(j.pt());         
    JetEta.push_back(j.eta());       
    JetPhi.push_back(j.phi());       
    JetEnergy.push_back(j.energy());
    JetBdisc.push_back(j.bDiscriminator("combinedSecondaryVertexBJetTags"));
    JetMass.push_back(j.mass());
    //  JetParton.push_back(j.partonFlavour());
    //JetjetId.push_back(int(jetID(j)));                                   
    //JetIDPU.push_back(j.userFloat("pileupJetId:fullDiscriminant"));
    //Jetpass_pileupJetId.push_back(pu_mva::pass_id(j, j.userFloat("pileupJetId:fullDiscriminant")));
    Jetnh_e.push_back(j.neutralHadronEnergy());                               
    Jetne_e.push_back(j.neutralEmEnergy());                                   
    Jethe_e.push_back(j.chargedHadronEnergy());                               
    JetcEmEnergy.push_back(j.chargedEmEnergy());                              
    JetMuonEnergy.push_back(j.muonEnergy());                                  
    JetEleEnergy.push_back(j.electronEnergy());                               
    JetPhotonEnergy.push_back(j.photonEnergy());                              
    UncorrJetPt.push_back(j.correctedJet("Uncorrected").pt());                
    
  } 
  
}

void JetSelector::SetBranches(){

  if(debug_)    std::cout<<"setting branches: calling AddBranch of baseTree"<<std::endl;
  AddBranch(&JetPt,      "JetPt");
  AddBranch(&JetEta,     "JetEta");
  AddBranch(&JetPhi,     "JetPhi");
  AddBranch(&JetEnergy,  "JetEnergy");
  AddBranch(&JetBdisc,   "JetBdisc");
  AddBranch(&JetMass,    "JetMass");
  // AddBranch(&JetParton,  "JetParton");   
  //AddBranch(&JetjetId,   "JetjetId");
  //AddBranch(&JetIDPU,    "JetIDPU"); 
  //AddBranch(&Jetpass_pileupJetId, "Jetpass_pileupJetId");
  AddBranch(&Jetnh_e, "Jetnh_e");
  AddBranch(&Jetne_e,"Jetne_e");
  AddBranch(&Jethe_e,"Jethe_e");
  AddBranch(&JetcEmEnergy,"JetcEmEnergy");
  AddBranch(&JetMuonEnergy,"JetMuonEnergy");
  AddBranch(&JetEleEnergy,"JetEleEnergy");
  AddBranch(&JetPhotonEnergy,"JetPhotonEnergy");
  AddBranch(&UncorrJetPt,"UncorrJetPt");


  if(debug_)    std::cout<<"set branches"<<std::endl;
}

void JetSelector::Clear(){
  
  JetPt.clear();
  JetEta.clear();
  JetPhi.clear();
  JetEnergy.clear();
  JetBdisc.clear();
  JetMass.clear();
  // JetParton.clear();
  //JetjetId.clear();
  //JetIDPU.clear();
  //Jetpass_pileupJetId.clear();
  Jetnh_e.clear();
  Jetne_e.clear();
  Jethe_e.clear();
  JetcEmEnergy.clear();
  JetMuonEnergy.clear();
  JetEleEnergy.clear();
  JetPhotonEnergy.clear();
  UncorrJetPt.clear();

}
