#include "run.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager * man = G4AnalysisManager::Instance();

    // Ntuple for process-name and endpoint coordinates in LH2 target
    man->CreateNtuple("LH2", "LH2");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleSColumn("fProc");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);
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
