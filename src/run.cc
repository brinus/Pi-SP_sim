#include "run.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager * man = G4AnalysisManager::Instance();

    // Ntuple for FDet data
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvents");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);

    // Ntuple for process-name in LH2 target
    man->CreateNtuple("Porcess_name", "Process_name");
    man->CreateNtupleSColumn("fProc");
    man->FinishNtuple(1);

    // Ntuple for ending point of pi- in LH2 target
    man->CreateNtuple("Pion_EP", "Pion_EP");
    man->CreateNtupleIColumn("fEvents");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(2);
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
