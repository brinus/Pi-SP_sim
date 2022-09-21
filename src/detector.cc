#include "detector.hh"
#include <iostream>

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

MySDParticleFilter::MySDParticleFilter(G4String name, G4String PID) : G4SDParticleFilter(name, PID)
{}

MySDParticleFilter::~MySDParticleFilter()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step * aStep, G4TouchableHistory *ROhist)
{
    G4Track * track = aStep->GetTrack();

    G4StepPoint * preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint * postStepPoint = aStep->GetPostStepPoint();

    G4String SDName = preStepPoint->GetSensitiveDetector()->GetName();
    G4ThreeVector posPion = preStepPoint->GetPosition();
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    if (SDName == "sensFDet"){
        man->FillNtupleIColumn(0, 0, evt);
        man->FillNtupleDColumn(0, 1, posPion[0]);
        man->FillNtupleDColumn(0, 2, posPion[1]);
        man->FillNtupleDColumn(0, 3, posPion[2]);
        man->AddNtupleRow(0);
        }

    if (SDName == "sensLH2"){
        if (track->GetTrackStatus() == 2){ // 2 == fStopAndKill
            G4String proc = preStepPoint->GetProcessDefinedStep()->GetProcessName();
            man->FillNtupleSColumn(1, 0, proc);
            man->FillNtupleDColumn(1, 1, posPion[0]);
            man->FillNtupleDColumn(1, 2, posPion[1]);
            man->FillNtupleDColumn(1, 3, posPion[2]);
            man->AddNtupleRow(1);
        }
    }

    return 0;
}