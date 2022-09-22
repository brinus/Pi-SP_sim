#include <iostream>
#include <vector>
#include <string>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "construct.hh"
#include "physics.hh"
#include "action.hh"

bool isPositiveNumber(char number[])
{
    int i = 0;
    if (number[0] == '-')
        return false;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

G4UImanager * init(int argc, char** argv)
{
   G4Random::setTheEngine(new CLHEP::RanecuEngine());
   G4long seed = time(NULL);
   G4Random::setTheSeed(seed);

   G4RunManager *runManager = new G4RunManager();	
   runManager->SetUserInitialization(new MyDetectorConstruction());
   runManager->SetUserInitialization(new MyPhysicsList());
   runManager->SetUserInitialization(new MyActionInitialization());
   runManager->Initialize();

   G4VisManager *visManager = new G4VisExecutive();
   visManager->Initialize();

   G4UImanager *UImanager = G4UImanager::GetUIpointer();
   return UImanager;
}

int main(int argc, char** argv){

   std::vector<std::string> keywords = {"vis", "beamOn", "help"};

   G4UIExecutive *ui = nullptr;
   if (argc == 1 || argv[1] == keywords[0]) ui = new G4UIExecutive(argc, argv);

   std::cout << "\n\n---------------------- STARTING PROGRAM ----------------------\n" << std::endl;
   std::cout << " Author: Matteo Brini" << std::endl;
   std::cout << " Project: Pi-SP" << std::endl;
   std::cout << " Description: pi- stopping power in LH2 target inside a stain steel tank" << std::endl;
   std::cout << " Git-Hub repository link: https://github.com/brinus/Pi-SP_sim\n" << std::endl;
   std::cout << "--------------------------------------------------------------\n" << std::endl;

   if (argc == 1){
      G4UImanager * UImanager = init(argc, argv);
      UImanager->ApplyCommand("/control/execute vis.mac");
   }
   else if (argv[1] == keywords[0]){                  // vis
      G4UImanager * UImanager = init(argc, argv);
      UImanager->ApplyCommand("/control/execute vis.mac");
   }
   else if (argv[1] == keywords[1] && argc == 2){     // beamOn
      G4UImanager * UImanager = init(argc, argv);
      UImanager->ApplyCommand("/run/beamOn 100");
      return 0;
   }
   else if (argv[1] == keywords[1] && argc == 3){     
      std::string events = argv[2];
      if (isPositiveNumber(argv[2])){
         G4UImanager * UImanager = init(argc, argv);
         UImanager->ApplyCommand("/run/beamOn " + events);
      }
      else{
         std::cout << "Error: the argument after beamOn is not of int type" << std::endl;
         std::cout << " $ ./sim beamOn " + events << std::endl;
         std::cout << "                ^" << std::endl;
         return 0;
      }
   }
   else if (argv[1] == keywords[2] && argc == 2){     // help
      std::cout << "\n Pi-SP_sim Help:\n" << std::endl;
      std::cout << "Pi-SP_sim/build $ ./sim [command] [option]\n" << std::endl;
      std::cout << "             - Simulation starts in GUI mode" << std::endl;
      std::cout << "         vis - Simulation starts in GUI mode" << std::endl;
      std::cout << "  beamOn [x] - Simulation starts in batch mode, executing macro /run/beamOn [x]," << std::endl;
      std::cout << "               where [x] is an integer passed as input (if not, defalut is [x] = 100)\n" << std::endl;
      return 0;
   }
   ui->SessionStart();

   return 0;
}