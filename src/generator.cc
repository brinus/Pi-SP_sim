#include "generator.hh"
#include "TF1.h"
#include "TMath.h"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    particle = particleTable->FindParticle("pi-");
    fParticleGun = new G4ParticleGun(1);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4bool flag_gen = 0;

    if (flag_gen)
    {
        TF1 *fMomentum = new TF1("fMomentum", "gaus", 0, 1000);
        fMomentum->SetParameters(1, 70.5, 0.898);

        TF1 *fTheta = new TF1("fTheta", "1", -0.0523, 0.0523);
        TF1 *fPhi = new TF1("fPhi", "1", 0, 2 * TMath::Pi());

        theta = fTheta->GetRandom();
        phi = fPhi->GetRandom();

        x_0 = TMath::Sin(theta) * TMath::Cos(phi);
        y_0 = TMath::Sin(theta) * TMath::Sin(phi);
        z_0 = TMath::Cos(theta);

        momentum = fMomentum->GetRandom() * MeV;

        delete fMomentum;
        delete fTheta;
        delete fPhi;
    }

    else
    {
        x_0 = 0;
        y_0 = 0;
        z_0 = 1;

        momentum = 70.5 * MeV;
    }

    pos = G4ThreeVector(0., 0., -0.1 * m);
    mom = G4ThreeVector(x_0, y_0, z_0);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(momentum);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
