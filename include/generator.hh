#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4GenericMessenger.hh"

#include "TLorentzVector.h"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *);

private:
    G4GenericMessenger *fMessenger;

    G4ParticleGun *fParticleGun;
    
    G4bool gamma;
    G4ThreeVector pos, mom;
    G4double momentum, x_0, y_0, z_0, theta, phi;

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle;
};

#endif