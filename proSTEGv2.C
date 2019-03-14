#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TRandom3.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
#define PI2 2.0*3.141592653589793
 
const Int_t maxnh = 20000;
Int_t b_npg, b_n, n;
Float_t b_ptg[maxnh], b_etag[maxnh], b_phig[maxnh];
Float_t b_phirg;

void proSTEGv2()
{

  int tot_num=500;  // number of events
  double MeanMult=200; // number of particle per event
  double RMSMult=0;

  //simple toy event generator
  TFile f("steg_output_flow.root", "RECREATE","ROOT file with histograms & tree");
  TTree *tree = new TTree("tree","Event tree with a few branches");
  tree->Branch("n", &b_n, "n/I");          // number of particles
  tree->Branch("ptg", &b_ptg, "ptg[n]/F");  // pt, transverse momentum
  tree->Branch("etag", &b_etag, "etag[n]/F"); // eta, rapidity
  tree->Branch("phig", &b_phig, "phig[n]/F"); // phi, angle
  tree->Branch("phirg", &b_phirg, "phirg/F");  // RP angle;  

  TF1 *EtaDistr = new TF1("EtaDistr","exp(-(x-2.1)^2/6.3)+exp(-(x+2.1)^2/6.3)",-2.4,2.4);
  TF1 *PhiDistr = new TF1("PhiDistr","1+2*[0]*cos(2*x)+2*[1]*cos(3*x)",0,PI2);

  //TF1 *PtDistr  = new TF1("PtDistr","exp (-(x/.40))+0.0015*exp (-(x/1.5))", 0.2,10);
  TF1 *PtDistr  = new TF1("PtDistr","exp (-(x/0.90))+0.15*exp (-(x/15))", 0.2,10);

  TF1 *V2vsPt = new TF1("V2vsPt","((x/3.4)^1.8/(1+(x/3)^1.8))*(.00005+(1/x)^0.8)",0.2,10); 


  TRandom3 *rnd;
  rnd = new TRandom3(0);
  
  double myphi, mypt, myeta;
  double v2, Psi;  

  for(int i=0; i<tot_num; i++){ 
    
    Psi = rnd->Uniform(0.0,PI2);
    //Psi = 0;
    b_phirg = Psi;

    b_npg = rnd->Gaus(MeanMult,RMSMult); 
    n = 0;
  
    for(int j=0; j<b_npg;j++ ){
     
      mypt = PtDistr->GetRandom();
      myeta =  EtaDistr->GetRandom();
      v2=V2vsPt->Eval(mypt);

      b_etag[n] = myeta;
      b_ptg[n]  = mypt;

      //PhiDistr->SetParameters(0.0,0.0);
      PhiDistr->SetParameters(v2,0.0);
      
      myphi = PhiDistr->GetRandom(); // randon selection dn/dphi
      myphi = myphi+Psi;
      if (myphi>PI2) myphi=myphi-PI2; // in the range of: 0 - 2*Pi      

      b_phig[n] = myphi; // save angle in lab frame
         
      n++;
      
    } // End of loop over particles
 
    if (i%20 == 0) cout << i << " " << "events processed" << endl;

    b_n = n;
    tree->Fill();
  } // End of loop over events
  
  cout << "writing tree" << endl;
  //tree->Write();
  cout << "writing to file" << endl;
  f.Write();
  cout << "closing file" << endl;
  f.Close();
  cout << "THE END" << endl;
}

