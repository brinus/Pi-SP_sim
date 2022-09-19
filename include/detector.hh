#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4SDParticleFilter.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
    public:
        MySensitiveDetector(G4String);
        ~MySensitiveDetector();

    private:
        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

class MySDParticleFilter : public G4SDParticleFilter
{
    public:
        MySDParticleFilter(G4String, G4String);
        ~MySDParticleFilter();
};

#endif