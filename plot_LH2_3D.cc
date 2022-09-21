#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH3F.h"
#include "TF1.h"

#include "TStyle.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TGaxis.h"
#include "TPad.h"
#include "TCut.h"
#include "TString.h"
#include "TAxis3D.h"

void fancyPlot(TH1F * plt){
    plt->GetXaxis()->SetTitle("z [mm]"); plt->GetXaxis()->SetTitleSize(0.045);
    plt->GetYaxis()->SetTitle("occurrencies"); plt->GetYaxis()->SetTitleSize(0.045);
    plt->GetYaxis()->SetTitleOffset(1.05);
}

void plot_LH2_3D(){
    
    // ---------- INITIAL SETTINGS ------------------------

    gStyle->SetOptStat("e"); gStyle->SetOptFit(1111);
    gStyle->SetStatBorderSize(0.); gStyle->SetTextSize(19);
    gStyle->SetStatX(.35); gStyle->SetStatY(.35); 
    gStyle->SetMarkerStyle(20); gStyle->SetMarkerSize(0.2);

    // ---------- VARAIBLES -------------------------------

    std::vector<TH3F *> vHist;
    std::set<Char_t *> uProc;
    Char_t proc_name[20];
    Int_t i = 0;

    TCanvas * c1 = new TCanvas("c1", "c1", 1);
    
    TFile * f = new TFile("build/output.root", "read");
    if (!f){
        printf("Cannot get the TFile\n");
        return;
    }

    TTree * data = (TTree *)f->Get("LH2");
    if (!data){
        printf("Cannot get the TNtuple\n");
        return;
    }
    data->SetBranchAddress("fProc", &proc_name);
    for (i = 0; i < data->GetEntries(); i++){
        data->GetEntry(i);
        uProc.insert(proc_name);
    }
    std::cout << uProc.size() << std::endl;

    i = 0;
    for (Char_t * key: uProc){
        TString cut("fProc==\"");
        vHist.push_back(new TH3F());
        data->Draw("fX:fY:fZ >> hist", cut.Append(key).Append("\""));
        vHist[i] = (TH3F *)gDirectory->Get("hist");
        vHist[i]->SetMarkerStyle(20);
        vHist[i]->SetMarkerSize(0.2);
        vHist[i]->SetMarkerColor(i+2);
        c1->Update();
        i++;
    }

    i = 2;
    c1->Clear();

    for (i = 0; i < vHist.size(); i++){
        vHist[i]->SetMarkerColor(i+2);
        vHist[i]->Draw("SAME");
        i++;
    }

    TAxis3D rulers;
    rulers.Draw();
    c1->Update();
    // ----------- PLOT -----------------------------------

}