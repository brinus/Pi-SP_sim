# Pi-SP_sim
Geant4 simulation for studying target stopping power with a pi-(momentum 70.5 MeV/c) beam, used in MEG II collaboration

## How to run the program
Starting from the project directory:
```
Pi-SP_sim $ mkdir build
Pi-SP_sim $ cd build
```
Now we can compile the project:
```
Pi-SP_sim/build $ cmake ..
Pi-SP_sim/build $ make
```

## Options
To have a full preview on how to run the program, simply write:
```
Pi-SP_sim/build $ ./sim help

 Pi-SP_sim Help:

Pi-SP_sim/build $ ./sim [command] [option]

             - Simulation starts in GUI mode
         vis - Simulation starts in GUI mode
  beamOn [x] - Simulation starts in batch mode, executing macro /run/beamOn [x],
               where [x] is an integer passed as input (if not, defalut is [x] = 100)
```
E.g.: to run in batch mode with 1000 events, write:
```
Pi-SP_sim/build $ ./sim beamOn 1000
```

## ROOT output
As default, everytime a run is started, the program will make a file `output.root` in the `build` folder. The file contains the following TNtuples:
  1. FDet: information about the $\pi^-$ in the first detector.
      * fEvents (int): ID number of the event.
      * fX (double): X position of the $\pi^-$.
      * fY (double): Y position of the $\pi^-$.
      * fZ (double): Z position of the $\pi^-$.
  2. LH2: information about the process occurred at the end of the $\pi^-$ life in the LH2 target.
      * fProc (string): name of the occurred process.
      * fX (double): final X position of the $\pi^-$.
      * fY (double): final Y position of the $\pi^-$.
      * fZ (double): final Z position of the $\pi^-$.

The user can analyze the results contained in the file using the two scripts `plot_3d.py` and `plot_LH2.cc` in the project folder, or simply open a ROOT terminal to explore the file with a TBrowser.
