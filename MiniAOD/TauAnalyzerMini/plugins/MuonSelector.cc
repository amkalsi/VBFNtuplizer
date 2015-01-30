#include "MuonSelector.h"

MuonSelector::MuonSelector(std::string name, TTree* tree, bool debug, const pset& iConfig):baseTree(name,tree,debug){
  
  SetBranches();
  muonToken_ = iConfig.getParameter<edm::InputTag>("muons");
// tauToken_  = iConfig.getParameter<edm::InputTag>("taus");
//   muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
//     8     electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
//       9     tauToken_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("taus"))),
//
 vertexInputTag = iConfig.getParameter<edm::InputTag>("vertices");
}

MuonSelector::~MuonSelector(){
  delete tree_;
}

void MuonSelector::Fill(const edm::Event& iEvent){
  Clear();
  
  int mucoun = 0;
  
  edm::Handle<edm::View<pat::Muon> > muon_h;
  iEvent.getByLabel(muonToken_, muon_h);

  edm::Handle<reco::VertexCollection> vtx_h;
  iEvent.getByLabel(vertexInputTag, vtx_h);

   reco::VertexCollection::const_iterator firstGoodVertex = vtx_h->end();
   for (reco::VertexCollection::const_iterator it = vtx_h->begin(); it != firstGoodVertex; it++)
    {
     isGoodVertex(*it);
     firstGoodVertex = it;
     break;
    }
 // require a good vertex 
    if (firstGoodVertex == vtx_h->end()) return;
    
    for(edm::View<pat::Muon>::const_iterator mu = muon_h->begin(); mu != muon_h->end(); mu++){
    if (mu->pt() < 10 || !mu->isLooseMuon()) continue;
    if (fabs(mu->eta()) > 2.4) continue;  
    //  printf("mu->n with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
    // mu->pt(), mu->mu->nBestTrack()->dz(PV.position()), mu->isLooseMuon(), mu->isTightMuon(PV));
    
    reco::TrackRef gtk = mu->globalTrack();
    
    MuonPt.push_back(mu->pt());
    MuonEta.push_back(mu->eta());
    MuonPhi.push_back(mu->phi());
    MuonP.push_back(mu->p());
    
    MuonCharge.push_back(mu->charge());
    if(gtk.isNonnull()){
      MuonChi2.push_back(gtk->normalizedChi2());
      MuonValidHits.push_back(gtk->hitPattern().numberOfValidMuonHits()); 
    } else {                
      MuonChi2.push_back(-9999);
      MuonValidHits.push_back(-9999);
      
    }
    MuonMatchedStat.push_back(mu->numberOfMatchedStations());
    MuonDXY.push_back(mu->muonBestTrack()->dxy(firstGoodVertex->position())); 
    
    if(mu->innerTrack().isNonnull()){
      MuonValidHitsInner.push_back(mu->innerTrack()->hitPattern().numberOfValidPixelHits());
      MuonTLayers.push_back(mu->innerTrack()->hitPattern().trackerLayersWithMeasurement());
    } else {
      MuonValidHitsInner.push_back(-999);
      MuonTLayers.push_back(-999);
    }
    
    MuonDZ.push_back(mu->muonBestTrack()->dz(firstGoodVertex->position()));
    MuonTight.push_back(mu->isTightMuon(*firstGoodVertex));
    MuonSoft.push_back(mu->isSoftMuon(*firstGoodVertex));
    MuonPF.push_back(mu->isPFMuon());   
    MuonEnergy.push_back(mu->energy());
    MuonRel.push_back((mu->trackIso() + mu->ecalIso() + mu->hcalIso()));
    MuonIsoCharParPt.push_back((mu->pfIsolationR04().sumChargedParticlePt));
    MuonIsoCharged.push_back((mu->pfIsolationR04().sumChargedHadronPt));
    MuonIsoNeutralHadron.push_back((mu->pfIsolationR04().sumNeutralHadronEt));
    MuonIsoPhoton.push_back((mu->pfIsolationR04().sumPhotonEt));
    MuonIsoPU.push_back((mu->pfIsolationR04().sumPUPt));
    
    
    mucoun++;
  }
  
  
}

void MuonSelector::SetBranches(){
  if(debug_)    std::cout<<"setting branches: calling AddBranch of baseTree"<<std::endl;
  /*  AddBranch(&GenJetAK5Pt           ,"GenJetAK5Pt");
      AddBranch(&GenJetAK5Eta	   ,"GenJetAK5Eta");     
      AddBranch(&GenJetAK5Phi	   ,"GenJetAK5Phi");     
      AddBranch(&GenJetAK5Energy	   ,"GenJetAK5Energy");  
      AddBranch(&GenJetAK5Mass	   ,"GenJetAK5Mass");    
      AddBranch(&GenJetAK5P		   ,"GenJetAK5P");       
      AddBranch(&GenJetemf		   ,"GenJetemf");        
      AddBranch(&GenJethadf		   ,"GenJethadf");       
      AddBranch(&PFJetPt		   ,"PFJetPt");          
      AddBranch(&PFJetEta		   ,"PFJetEta");         
      AddBranch(&PFJetPhi		   ,"PFJetPhi");         
      AddBranch(&PFJetEnergy	   ,"PFJetEnergy");      
      AddBranch(&PFJetMass		   ,"PFJetMass");        
      AddBranch(&PFJetP		   ,"PFJetP");    
  */
  
  AddBranch(&MuonPt                ,"MuonPt");
  AddBranch(&MuonEta               ,"MuonEta");
  AddBranch(&MuonPhi               ,"MuonPhi");
  AddBranch(&MuonP                 ,"MuonP");
  AddBranch(&MuonEnergy            ,"MuonEnergy");
  AddBranch(&MuonCharge            ,"MuonCharge");
  AddBranch(&MuonChi2              ,"MuonChi2");
  AddBranch(&MuonValidHits         ,"MuonValidHits");
  AddBranch(&MuonValidHitsInner    ,"MuonValidHitsInner");
  AddBranch(&MuonMatchedStat       ,"MuonMatchedStat");
  AddBranch(&MuonDXY               ,"MuonDXY");
  AddBranch(&MuonTLayers           ,"MuonTLayers");
  AddBranch(&MuonDZ                ,"MuonDZ");
  AddBranch(&MuonTight             ,"MuonTight");
  AddBranch(&MuonSoft              ,"MuonSoft");
  AddBranch(&MuonPF                ,"MuonPF");
  AddBranch(&MuonIsoCharged        ,"MuonIsoCharged");
  AddBranch(&MuonRel               ,"MuonRel");
  AddBranch(&MuonIsoCharParPt      ,"MuonIsoCharParPt");
  AddBranch(&MuonIsoNeutralHadron  ,"MuonIsoNeutralHadron");
  AddBranch(&MuonIsoPhoton         ,"MuonIsoPhoton");
  AddBranch(&MuonIsoPU             ,"MuonIsoPU");

  if(debug_)    std::cout<<"set branches"<<std::endl;
}

void MuonSelector::Clear(){
  
  /*GenJetAK5Pt.clear();
  GenJetAK5Eta.clear();
  GenJetAK5Phi.clear();
  GenJetAK5Energy.clear();
  GenJetAK5Mass.clear();
  GenJetAK5P.clear();
  GenJetemf.clear();
  GenJethadf.clear();
  PFJetPt.clear();
  PFJetEta.clear();
  PFJetPhi.clear();
  PFJetEnergy.clear();
  PFJetMass.clear();
  PFJetP.clear();
  */

  MuonPt.clear();
  MuonEta.clear();
  MuonPhi.clear();
  MuonEnergy.clear();
  MuonDZ.clear();
  MuonTight.clear();
  MuonSoft.clear();
  MuonPF.clear();   
  MuonIsoCharged.clear();
  MuonIsoNeutralHadron.clear();
  MuonIsoPhoton.clear();
  MuonIsoPU.clear();
  MuonP.clear(); 
  MuonCharge.clear(); 
  MuonChi2.clear(); 
  MuonValidHits.clear();
  MuonValidHitsInner.clear(); 
  MuonMatchedStat.clear(); 
  MuonDXY.clear(); 
  MuonTLayers.clear(); 

}

bool MuonSelector::isGoodVertex(const reco::Vertex& vtx)
{
if (vtx.isFake()) return false;
if (vtx.ndof() < 4) return false;
if (vtx.position().Rho() > 2.) return false;
if (fabs(vtx.position().Z()) > 24.) return false;
return true;
}
