#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4VUserPhysicsList.hh"

#include "G4PionMinus.hh"
#include "G4PionZero.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4Gamma.hh"

#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"

#include "G4Transportation.hh"
#include "G4ChargeExchangeProcess.hh"
#include "G4Decay.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
public:
    MyPhysicsList();
    ~MyPhysicsList();
};

class MyUserPhysicsList : public G4VUserPhysicsList
{
public:
    MyUserPhysicsList();
    ~MyUserPhysicsList();

    virtual void ConstructParticle();
    virtual void ConstructEM();
    virtual void ConstructProcess();

    void ContructGeneral();
};

#endif