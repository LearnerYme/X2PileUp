#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TChain.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TString.h"

#include "tree_reader.h"
#include "Conf.h"

int main(){
    using std::cout;
    using std::string;
    using std::vector;
    using std::ifstream;
    vector<string> file_list;
    ifstream fin("file.list");
    string strtmp;
    int n_file = 0;
    while (std::getline(fin, strtmp)){
        n_file ++;
        if (n_file % 500 == 0){
            cout << "[LOG] " << n_file << " files found.\n";
        }
        file_list.push_back(strtmp);
    }
    cout << "[LOG] All " << n_file << " files found.\n";

    TChain* chain = new TChain("centTree");

    Int_t ifile = 0;
    for (auto iter=file_list.begin(); iter!=file_list.end(); iter++){
        ifile ++;
        if (ifile % 500 == 0){
            cout << "[LOG] " << ifile << " trees read.\n";
        }
        chain->Add(iter->c_str());
    }
    cout << "[LOG] All " << ifile << " trees read.\n";

    cout << "[LOG] Preparing to get histograms.\n";
    TreeReader* maker = new TreeReader();
    maker->init_reader(chain);
    Int_t nev = maker->get_entries();

    CentUtil* corr = maker->get_cent_util();
    corr->SetDoPileUp(true);
    corr->SetDoLumi(false);
    corr->SetDoVz(false);
    corr->ReadParams();

    TH1F* h1Ref3 = new TH1F("h1RefMult3", ";RefMult3;", 850, -0.5, 849.5);

    TH2F* h2Ref3VsNTofMatch = new TH2F(
        "h2Ref3VsNTofMatch", ";RefMult3;nTofMatch",
        850, -0.5, 849.5,
        300, -0.5, 299.5
    );
    TH2F* h2Ref3VsBetaEta1 = new TH2F(
        "h2Ref3VsBetaEta1", ";RefMult3;beta_eta1",
        850, -0.5, 849.5,
        500, -0.5, 499.5
    );

    for (Int_t i=0; i<nev; i++) {
        maker->make(i);
        int trg = maker->get_converted_trg();
        if (trg < 0 || trg >= cent_conf::nTrg) {
            continue;
        }
        if (corr->IsPileUp(maker->ref3, maker->beta_eta1, maker->nTofMatch)) { continue; }
        h1Ref3->Fill(maker->ref3);
        h2Ref3VsNTofMatch->Fill(maker->ref3, maker->nTofMatch);
        h2Ref3VsBetaEta1->Fill(maker->ref3, maker->beta_eta1);
    }


    cout << "[LOG] All done, now saving.\n";
    TFile* tfout = new TFile("pile_up_corr.root", "recreate");
    tfout->cd();
    h1Ref3->Write();
    h2Ref3VsBetaEta1->Write();
    h2Ref3VsNTofMatch->Write();
    tfout->Close();
    cout << "[LOG] This is the end of this workshop.\n";
    return 0;
}