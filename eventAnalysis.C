#include <stdio.h>
#include <complex>
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include <TMath.h>
using namespace std; 
void eventAnalysis(){

     long nEvt, nEvtProcess; 

     Int_t nParticle, iParticle;
     Float_t phi[20000];
     Float_t pt[20000];
     Float_t eta[20000];
     TH1D *histPt = new TH1D("histPt", "histPt", 200,0,10);

     //TH2D *hist2DV2yDiffVsV2xDiff = new TH2D("hist2DV2yDiffVsV2xDiff","hist2DV2yDiffVsV2xDiff", 200, -0.5,0.5, 200,-0.5,0.5);

     TChain t1("t1");
     t1.Add("./steg_output_events.root/tree");
     t1.SetBranchAddress("n", &nParticle);
     t1.SetBranchAddress("ptg", &pt);
     t1.SetBranchAddress("etag", &eta);
     t1.SetBranchAddress("phig", &phi);

     nEvt=t1.GetEntries();
     //nEvtProcess=50;
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%20==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1.GetEntry(ne);

       for(iParticle=0; iParticle<nParticle; iParticle++){
           //cout<<"evtID = "<<ne<<",  particlesPt = "<<pt[iParticle]<<",  particlePhi = "<<phi[iParticle]<<endl;
           histPt->Fill(pt[iParticle]);
       }


      } // end of event loop

      histPt->Draw();

}


