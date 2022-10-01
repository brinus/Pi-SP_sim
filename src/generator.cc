#include "generator.hh"
#include "TF1.h"
#include "TMath.h"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    gamma = false;
    fMessenger = new G4GenericMessenger(this, "/generator/", "Generator process");
    fMessenger->DeclareProperty("gamma", gamma, "Select to generate gamma in the LH2 instead of pi- outside of the cylinder");

    if (!gamma)
    {
        particle = particleTable->FindParticle("pi-");
        fParticleGun = new G4ParticleGun(1);
    }
    else
    {
        particle = particleTable->FindParticle("gamma");
        fParticleGun = new G4ParticleGun(2);
    }
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    if (!gamma)
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
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
    else
    {
        TF1 * gammaE = new TF1("gammaE", "1", 50, 80);

        pos = G4ThreeVector(0,0,0);
        mom = G4ThreeVector(0,0,0);
        momentum = 134.97/2 * MeV;

        // Gamma 1
        fParticleGun->SetParticlePosition(pos);
        fParticleGun->SetParticleMomentumDirection(mom);
        fParticleGun->SetParticleMomentum(momentum);
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->GeneratePrimaryVertex(anEvent);

        // Gamma 2
        fParticleGun->SetParticlePosition(pos);
        fParticleGun->SetParticleMomentumDirection(mom);
        fParticleGun->SetParticleMomentum(momentum);
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->GeneratePrimaryVertex(anEvent);
        delete gammaE;
    }



    
}
