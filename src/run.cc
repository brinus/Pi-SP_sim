#include "run.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager * man = G4AnalysisManager::Instance();

    // Ntuple for FDet data
    man->CreateNtuple("FDet", "FDet");
    man->CreateNtupleIColumn("fEvents");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);

    // Ntuple for process-name and endpoint coordinates in LH2 target
    man->CreateNtuple("LH2", "LH2");
    man->CreateNtupleSColumn("fProc");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(1);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run *)
{
    G4AnalysisManager * man = G4AnalysisManager::Instance();
    
    man->OpenFile("output.root");

}

void MyRunAction::EndOfRunAction(const G4Run *)
{
    G4AnalysisManager * man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
