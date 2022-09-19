#include "run.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager * man = G4AnalysisManager::Instance();

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvents");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);

    man->CreateNtuple("Porcess name", "Process name");
    man->CreateNtupleSColumn("fProc");
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
