/**
 * @file mScan.cpp
 * @author Matteo Brini (brinimatteo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLine.h"

void mScan(){
    /**
     * @brief The macro opens a list of files named with fName, numbered with vLayers, with extention fType.
     * The files come as output of ./sim, TTree "LH2" is taken for each file, "fZ" branch is saved in a vector
     * of TH1F *.
     */

    gStyle->SetOptStat(0);

    // ---------- VARIABLES -------------------------------

    std::vector<TH1 *> vHist;
    std::string fName = "res/output.";
    std::string fType = ".root";
    std::vector<std::string> vLayers = {"0", "1", "2"};

    TH1 * h1 = new TH1F();
    TFile * f = new TFile();
    TTree * t = new TTree();

    // ---------- READ HISTOGRAMS -------------------------

    for (std::string layers : vLayers){
        f = new TFile((fName + layers + fType).c_str()); 
        t = (TTree *)f->Get("LH2");
        t->Draw("fZ >> hZ");
        h1 = (TH1F *)gDirectory->Get("hZ");
        vHist.push_back(h1);
    }

    // ---------- PLOT ------------------------------------

    // Canvas
    TCanvas * c1 = new TCanvas("c1", "c1", 1);

    // Legend
    TLegend * legend = new TLegend(0.65, 0.7, 0.85, 0.85, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(22);
    legend->SetFillColorAlpha(0,0.0);

    // Histograms
    for (Int_t i = 0; i < vHist.size(); i++){
        vHist[i]->Draw("same");
        vHist[i]->SetLineColor(i+2);
        legend->AddEntry(vHist[i], ("#Layers = " + vLayers[i]).c_str(), "LPF");
    }

    vHist[0]->SetTitle("Longitudinal profile, entries = 5000 x run, layer = 0.5 mm (stain steel); z [mm]; occurrencies");

    // Boundary lines
    c1->Update();
    TLine * lleft = new TLine(-35, 0, -35, c1->GetUymax()); lleft->Draw();
    TLine * lright = new TLine(35, 0, 35, c1->GetUymax()); lright->Draw();
    legend->Draw();

}