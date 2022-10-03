#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    RegisterPhysics ( new G4EmStandardPhysics());
    RegisterPhysics ( new G4ChargeExchangePhysics());
    RegisterPhysics ( new G4DecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}