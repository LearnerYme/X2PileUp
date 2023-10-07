#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "TString.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"

#include "CentUtil.h"

using std::cout;

class TreeReader{
    private:
        CentUtil* corr;
        TChain* chain;

        Int_t nev;


    public:
        Int_t trgid;
        Int_t ref3;
        Int_t ref3Raw;
        Int_t nTofMatch;
        Int_t beta_eta1;
        Int_t tofMult;
        Double_t vz;
        Double_t zdcx;

        TreeReader(){
            corr = new CentUtil();
            chain = 0;
        }

        ~TreeReader(){}

        CentUtil* get_cent_util() {
            // use this function to get the corr
            // in outter codes
            return corr;
        }

        void init_reader(TChain* chain_) {
            chain = chain_;
            chain->SetBranchAddress("TriggerId", &trgid);
            chain->SetBranchAddress("refMult3", &ref3);
            chain->SetBranchAddress("refMult3Raw", &ref3Raw);
            chain->SetBranchAddress("nTofMatch", &nTofMatch);
            chain->SetBranchAddress("Beta_eta1", &beta_eta1);
            chain->SetBranchAddress("tofMult", &tofMult);
            chain->SetBranchAddress("Vz", &vz);
            chain->SetBranchAddress("ZDCx", &zdcx);

            if (chain != 0) {
                nev = chain->GetEntries();
            } else {
                nev = -1;
            }
        }

        Int_t get_entries() {
            return nev;
        }

        void make(Int_t i){
            if (i >= nev) {
                cout << "[WARNING] " << i << " out of range (max entry: " << nev << ").\n";
                return;
            }

            chain->GetEntry(i);
            if (i % 100000 == 0){
                cout << "[LOG] " << i << " / " << nev << " events processed.\n";
            }
        }

        Int_t get_converted_trg() {
            // return the Trigger ID index (for array index use)
            return corr->ConvertTrg(trgid);
        }
};
