#include <iostream>

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"

#include "TStyle.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TGaxis.h"
#include "TPad.h"

void fancyPlot(TH1F * plt){
    plt->GetXaxis()->SetTitle("z [mm]"); plt->GetXaxis()->SetTitleSize(0.045);
    plt->GetYaxis()->SetTitle("occurrencies"); plt->GetYaxis()->SetTitleSize(0.045);
    plt->GetYaxis()->SetTitleOffset(1.05);
}

void plot_LH2_profile(){
    
    // ---------- INITIAL SETTINGS ------------------------

    gStyle->SetOptStat("e"); gStyle->SetOptFit(1111);
    gStyle->SetStatBorderSize(0.); gStyle->SetTextSize(19);
    gStyle->SetStatX(.35); gStyle->SetStatY(.35);

    // ---------- VARAIBLES -------------------------------

    Double_t X_pos, Y_pos, Z_pos;

    TCanvas * c1 = new TCanvas("c1", "c1", 1);
    TCanvas * c2 = new TCanvas("c2", "c2", 1);
    TH1F * h1 = new TH1F("fZ", "Longitudinal profile", 100, -40, 40);
    TH2F * hXY = new TH2F("fX:fY", "Transverse profile", 100, -30, 30, 100, -30, 30);
    TH1F *h1sum = new TH1F("h1sum","Longitudinal profile integral",100,-40, 40);
    
    TFile * f = new TFile("build/output.root");
    if (!f){
        printf("Cannot get the TFile\n");
        return;
    }

    TTree * data = (TTree *)f->Get("LH2");
    if (!data){
        printf("Cannot get the TNtuple\n");
        return;
    }
    
    data->SetBranchAddress("fX", &X_pos);
    data->SetBranchAddress("fY", &Y_pos);
    data->SetBranchAddress("fZ", &Z_pos);

    for (Int_t i=0; i<data->GetEntries(); i++){
        data->GetEntry(i);
        h1->Fill(Z_pos);
        hXY->Fill(X_pos, Y_pos);
    }

    // ----------- PLOT -----------------------------------

    // First TCanvas
    c1->cd();

    // Z profile
    h1->Draw();
    c1->Update();
    fancyPlot(h1);

    // Population
    Float_t sum = 0;
    for (Int_t i=1; i<=100; i++) {
        sum += h1->GetBinContent(i);
        h1sum->SetBinContent(i,h1->GetEntries() - sum);
    }
    Float_t rightmax = 1.1*h1sum->GetMaximum();
    Float_t scale = gPad->GetUymax()/rightmax;
    h1sum->SetLineColor(kRed);
    h1sum->Scale(scale);
    h1sum->Draw("same");

    // Population's axis
    TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
                              gPad->GetUxmax(), gPad->GetUymax(),
                              0,rightmax,510,"+L");
    axis->SetLineColor(kRed);
    axis->SetLabelColor(kRed);
    axis->Draw();
    c1->Update();

    // Second TCanvas
    c2->cd(); 

    // X-Y profile
    hXY->Draw("lego1");
    c2->Update();

}