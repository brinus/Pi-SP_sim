#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "construct.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv){

   G4Random::setTheEngine(new CLHEP::RanecuEngine());
   G4long seed = time(NULL);
   G4Random::setTheSeed(seed);

   G4RunManager *runManager = new G4RunManager();	
   runManager->SetUserInitialization(new MyDetectorConstruction());
   runManager->SetUserInitialization(new MyPhysicsList());
   runManager->SetUserInitialization(new MyActionInitialization());
   runManager->Initialize();

   G4UIExecutive *ui = new G4UIExecutive(argc, argv);
   
   G4VisManager *visManager = new G4VisExecutive();
   visManager->Initialize();

   G4UImanager *UImanager = G4UImanager::GetUIpointer();

   UImanager->ApplyCommand("/vis/open OGL");
   UImanager->ApplyCommand("/vis/drawVolume");
   UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
   UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
   UImanager->ApplyCommand("/vis/geometry/set/forceAuxEdgeVisible all");
   UImanager->ApplyCommand("/tracking/verbose 1");
   UImanager->ApplyCommand("/vis/scene/add/axes -0.2 -0.2 -0.2 0.1 m");

   ui->SessionStart();

   return 0;
}
