/*! \mainpage
 * This is the main page.
 */

/**
 * @file sim.cc
 * @author Matteo Brini (brinimatteo@gmail.com)
 * @brief Main file
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

/**
 * @brief Global struct to store usefull infos.
 *
 */
struct Configuration
{
   Configuration();
   bool vis;      ///< Flag for the visualization option.
   bool beamOn;   ///< Flag for the beamOn option.
   bool layers;   ///< Flag for layers.
   bool thick;    ///< Flag for thickness of degradators.
   char *zThick;  ///< Thickness of degradators in mm.
   char *nEvents; ///< Number to pass at beamOn macro.
   char *nLayers; ///< Number of layers.
};

Configuration::Configuration()
{
   vis = false;
   beamOn = false;
   layers = false;
   thick = false;
   zThick = "0.5";
   nEvents = "100";
   nLayers = "1";
}

Configuration gConfig;

/**
 * @brief Prints the help message.
 *
 * @details This message is printed when -h flag or wrong input is passed to the program.
 */
void PrintHelp()
{
   // Print the help message on screen

   std::cout << "\n Pi-SP_sim Help:\n"
             << std::endl;
   std::cout << "Pi-SP_sim/build $ ./sim [command] [option]\n"
             << std::endl;
   std::cout << "   -v, --vis            : Simulation starts in GUI mode" << std::endl;
   std::cout << "   -b [n], --beamOn [n] : Simulation starts in batch mode, if --vis is passed then GUI is launched." << std::endl;
   std::cout << "                          Executing macro /run/beamOn [n], where [n] is an integer passed as input." << std::endl;
   std::cout << "                          Defalut is [n] = 100." << std::endl;
   std::cout << "   -l [n], --layers [n] : Setting the number [n] of layers in the current simulation. Requires to" << std::endl;
   std::cout << "                          specify --vis or --beamOn." << std::endl;
   std::cout << "   -t [n], --thick [z]  : Setting the thickness [z] of layers in the current simulation. Requires" << std::endl;
   std::cout << "                          to specify --vis or --beamOn.\n"
             << std::endl;
}

/**
 * @brief Checks if input is a natural number.
 *
 * @param number String you want to check.
 * @return true input can be a natural number.
 * @return false input cannot be a natural number.
 */
bool IsPositiveNumber(const char number[])
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

/**
 * @brief Main function.
 *
 * @details Checks for user input flags, stores them in global variable gConfig. Controls for eventual errors.
 * Executes the program based on the activated flags in gConfig.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, const char **argv)
{

   std::cout << "\n\n---------------------- STARTING PROGRAM ----------------------\n"
             << std::endl;
   std::cout << " Author: Matteo Brini" << std::endl;
   std::cout << " Project: Pi-SP" << std::endl;
   std::cout << " Description: pi- stopping power in LH2 target inside a stain steel tank" << std::endl;
   std::cout << " Git-Hub repository link: https://github.com/brinus/Pi-SP_sim\n"
             << std::endl;
   std::cout << "--------------------------------------------------------------\n"
             << std::endl;

   for (int i = 1; i < argc; i++)
   {
      if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vis") == 0)
      {
         gConfig.vis = true;
      }
      else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--beamOn") == 0)
      {
         gConfig.beamOn = true;
         gConfig.nEvents = "100";
         if (i + 1 < argc && IsPositiveNumber(argv[i + 1]))
         {
            gConfig.nEvents = (char *)argv[i + 1];
            i++;
         }
      }
      else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--thick") == 0)
      {
         gConfig.thick = true;
         gConfig.zThick = (char *)argv[i + 1];
         i++;
      }
      else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--layers") == 0)
      {
         gConfig.layers = true;
         if (i + 1 < argc && IsPositiveNumber(argv[i + 1]))
         {
            gConfig.nLayers = (char *)argv[i + 1];
            i++;
         }
         else
         {
            std::cerr << "Option layers requires an integer in input." << std::endl;
            PrintHelp();
            return 1;
         }
      }
      else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
      {
         PrintHelp();
         return 1;
      }
      else if (argv[i][0] == '-')
      {
         std::cerr << "Unknown flag: " << argv[i] << "\n";
         PrintHelp();
         return 1;
      }
      else
      {
         std::cerr << "Unknown command: " << argv[i] << "\n";
         PrintHelp();
         return 1;
      }
   }

   if (argc == 1)
   {
      PrintHelp();
      return 1;
   }

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
   G4UIExecutive *ui = nullptr;

   if (gConfig.vis)
   {
      ui = new G4UIExecutive(argc, (char **)argv);
      UImanager->ApplyCommand("/control/execute vis.mac");
   }

   if (gConfig.thick)
   {
      if (gConfig.vis == false && gConfig.beamOn == false)
      {
         std::cout << "Run mode not specified: use --vis or --beamOn" << std::endl;
         PrintHelp();
         delete visManager;
         delete runManager;
         delete ui;
         return 0;
      }
      UImanager->ApplyCommand("/detector/thick " + (std::string)gConfig.zThick);
      UImanager->ApplyCommand("/run/reinitializeGeometry");
   }

   if (gConfig.layers)
   {
      if (gConfig.vis == false && gConfig.beamOn == false)
      {
         std::cout << "Run mode not specified: use --vis or --beamOn" << std::endl;
         PrintHelp();
         delete visManager;
         delete runManager;
         delete ui;
         return 0;
      }
      UImanager->ApplyCommand("/detector/layers " + (std::string)gConfig.nLayers);
      UImanager->ApplyCommand("/run/reinitializeGeometry");
   }

   if (gConfig.beamOn)
   {
      UImanager->ApplyCommand("/run/beamOn " + (std::string)gConfig.nEvents);
   }
   ui->SessionStart();
   delete visManager;
   delete runManager;
   delete ui;
   return 0;
}