/*! \mainpage
 * This is the main page.
 */

/** 
 * @file sim.cc
 * @author Matteo Brini (brinimatteo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "construct.hh"
#include "physics.hh"
#include "action.hh"

struct Configuration
{
   Configuration();
   bool vis;
   bool beamOn;
   char * nEvents;
};

Configuration::Configuration()
{
   vis = false;
   beamOn = false;
   nEvents = "100";
}

Configuration gConfig;

void PrintHelp()
{
   // Print the help message on screen

   std::cout << "\n Pi-SP_sim Help:\n" << std::endl;
   std::cout << "Pi-SP_sim/build $ ./sim [command] [option]\n" << std::endl;
   std::cout << "                        : Simulation starts in GUI mode" << std::endl;
   std::cout << "   -v, --vis            : Simulation starts in GUI mode" << std::endl;
   std::cout << "   -b [n], --beamOn [n] : Simulation starts in batch mode, if --vis is passed then GUI is launched." << std::endl;
   std::cout << "                          Executing macro /run/beamOn [n]," << std::endl;
   std::cout << "                          where [n] is an integer passed as input (defalut is [n] = 100)\n" << std::endl;
}

bool IsPositiveNumber(const char number[])
{

   int i = 0;
   if (number[0] == '-')
      return false;
   for (; number[i] != 0; i++){
      if (!isdigit(number[i]))
         return false;
   }
   return true;
}

G4UImanager * InitUI(int argc, const char** argv)
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

int main(int argc, const char** argv){

   std::cout << "\n\n---------------------- STARTING PROGRAM ----------------------\n" << std::endl;
   std::cout << " Author: Matteo Brini" << std::endl;
   std::cout << " Project: Pi-SP" << std::endl;
   std::cout << " Description: pi- stopping power in LH2 target inside a stain steel tank" << std::endl;
   std::cout << " Git-Hub repository link: https://github.com/brinus/Pi-SP_sim\n" << std::endl;
   std::cout << "--------------------------------------------------------------\n" << std::endl;

   G4UIExecutive * ui = nullptr;

   if (argc == 1){
      gConfig.vis = true;
      ui = new G4UIExecutive(argc, (char **)argv);
      G4UImanager * UImanager = InitUI(argc, argv);
      UImanager->ApplyCommand("/control/execute vis.mac");
   }

   for (int i = 1; i < argc; i++){
      if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vis") == 0){
         gConfig.vis = true;     
      }
      else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--beamOn") == 0){
         gConfig.beamOn = true;
         gConfig.nEvents = "100";
         if (IsPositiveNumber(argv[i+1])){
            gConfig.nEvents = (char *)argv[i+1];
            i++;
         }
      }
      else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
         PrintHelp();
         return 1;
      }
      else if (argv[i][0] == '-'){
         std::cerr << "Unknown flag: " << argv[i] << "\n\n";
         PrintHelp();
         return 1;
      }
      else{
         std::cerr << "Unknown command: " << argv[i] << "\n\n";
         PrintHelp();
         return 1;
      }
   }

   G4UImanager * UImanager = InitUI(argc, argv);

   if (gConfig.vis){
      ui = new G4UIExecutive(argc, (char **)argv);
      UImanager->ApplyCommand("/control/execute vis.mac");
   }
   if (gConfig.beamOn){
      UImanager->ApplyCommand("/run/beamOn " + (std::string)gConfig.nEvents);
   }
   ui->SessionStart();

   return 0;
}