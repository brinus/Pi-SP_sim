#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4ChargeExchangePhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
    RegisterPhysics(new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{
}

MyUserPhysicsList::MyUserPhysicsList()
{
    //ConstructParticle();
    //ConstructProcess();

    // RegisterPhysics(new G4EmStandardPhysics());
}

MyUserPhysicsList::~MyUserPhysicsList()
{
}

void MyUserPhysicsList::ConstructParticle()
{
    mConstructor.ConstructParticle();
    boConstructor.ConstructParticle();
    baConstructor.ConstructParticle();
    G4Gamma::Definition();
}

void MyUserPhysicsList::ConstructProcess()
{
    AddTransportation();
    ConstructEM();
    ContructGeneral();
}

void MyUserPhysicsList::ConstructEM()
{
    G4PhysicsListHelper *ph = G4PhysicsListHelper::GetPhysicsListHelper();
    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)())
    {
        G4ParticleDefinition *particleDefinition = particleIterator->value();
        if (particleDefinition == G4Gamma::Definition())
        {
            ph->RegisterProcess(new G4Decay(), particleDefinition);
        }
    }
}

void MyUserPhysicsList::ContructGeneral()
{
    G4PhysicsListHelper *ph = G4PhysicsListHelper::GetPhysicsListHelper();
    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)())
    {
        G4ParticleDefinition *particleDefinition = particleIterator->value();
        if (particleDefinition == G4PionMinus::Definition())
        {
            ph->RegisterProcess(new G4ChargeExchangeProcess(), particleDefinition);
        }
        else if (particleDefinition == G4PionZero::Definition())
        {
            ph->RegisterProcess(new G4ChargeExchangeProcess(), particleDefinition);
            ph->RegisterProcess(new G4Decay(), particleDefinition);
        }
        else if (particleDefinition == G4Proton::Definition())
        {
            ph->RegisterProcess(new G4ChargeExchangeProcess(), particleDefinition);
        }
        else if (particleDefinition == G4Neutron::Definition())
        {
            ph->RegisterProcess(new G4ChargeExchangeProcess(), particleDefinition);
        }
        // else if (particleDefinition == G4Gamma::Definition())
        // {
        //     ph->RegisterProcess(new G4Decay(), particleDefinition);
        // }
    }
}