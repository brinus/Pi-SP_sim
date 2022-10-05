#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics_option1());
    RegisterPhysics(new G4ChargeExchangePhysics());
    RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
    RegisterPhysics(new G4DecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{
}