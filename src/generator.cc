#include "generator.hh"
#include "TF1.h"
#include "TMath.h"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition * particle = particleTable->FindParticle("pi-");

    G4bool flag_gen = 0;
    G4double x_0, y_0, z_0, momentum;

    if (flag_gen){
        TF1 * fMomentum = new TF1("fMomentum", "gaus", 0, 1000);
        fMomentum->SetParameters(1, 70.5, 0.898);

        TF1 * fTheta = new TF1("fTheta", "1", -0.0523, 0.0523);
        TF1 * fPhi = new TF1("fPhi", "1", 0, 2*TMath::Pi());

        G4double theta = fTheta->GetRandom();
        G4double phi = fPhi->GetRandom();

        x_0 = TMath::Sin(theta) * TMath::Cos(phi);
        y_0 = TMath::Sin(theta) * TMath::Sin(phi);
        z_0 = TMath::Cos(theta);

        momentum = fMomentum->GetRandom()*MeV;
    }

    else{
        x_0 = 0;
        y_0 = 0;
        z_0 = 1;

        momentum = 70.5*MeV;
    }


    G4ThreeVector pos(0.,0.,-0.1*m);
    G4ThreeVector mom(x_0, y_0, z_0);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(momentum);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
