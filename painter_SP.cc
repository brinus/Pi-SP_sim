#include <iostream>

#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGeoManager.h"
#include "TGeoTube.h"

void painter_SP(){
    TFile * f = new TFile("build/output.root");
    if (!f){
        printf("Cannot get the TFile\n");
        return;
    }

    TTree * data = (TTree *)f->Get("Pion_EP");
    if (!data){
        printf("Cannot get the TNtuple\n");
        return;
    }

    TCanvas * c1 = new TCanvas("c1", "c1", 1);

    // Geometry 

    TGeoTube * LH2 = new TGeoTube(0, 30, 35);

    // Plotting
    c1->cd();
    data->Draw("fX:fY:fZ:fEvents", "", "colz");
    LH2->Draw("same");
}