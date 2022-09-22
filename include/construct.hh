#ifndef CONSTRUCT_HH
#define CONSTRUCT_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4GenericMessenger.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        MyDetectorConstruction();
        ~MyDetectorConstruction();

        virtual G4VPhysicalVolume * Construct();

    private:
        G4Box *solidWorld;
        G4Tubs *solidCyl_o, *solidCyl_v, *solidCyl_i, *solidLH2, *solidFDet, *solidThick;
        G4LogicalVolume *logicWorld, *logicCyl_o, *logicCyl_v, *logicCyl_i, *logicLH2, *logicFDet, *logicThick;
        G4VPhysicalVolume *physWorld, *physCyl_o, *physCyl_v, *physCyl_i, *physLH2, *physFDet, *physThick;

        G4double xWorld, yWorld, zWorld;

        G4Material *worldMat, *lH2, *inox, *vacuum;

        G4GenericMessenger * fMessenger;

        G4int layers;
        G4double thick;

        virtual void ConstructSDandField();
        void DefineMaterial();

};

#endif