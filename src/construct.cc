#include "construct.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume * MyDetectorConstruction::Construct()
{
    // ---------- VARIABLES -------------------------------
    
    G4NistManager * nist = G4NistManager::Instance();
    G4double density;

    G4VisAttributes * cGrey = new G4VisAttributes(G4Colour(0.8, 0.8, 0.8));
    cGrey->SetForceWireframe(true);

    G4VisAttributes * cWhite = new G4VisAttributes(G4Colour(1, 1, 1));
    cWhite->SetForceWireframe(true);

    // ---------- MATERIALS -------------------------------

    G4Material * worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Material * lH2 = new G4Material("Liquid hidrogen", density = 0.07085*g/cm3, 1, kStateLiquid);
    lH2->AddElement(nist->FindOrBuildElement("H"), 2);

    G4Material * inox = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

    G4Material * vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    // ---------- OBJECTS ---------------------------------
    
    // World
    G4Box * solidWorld = new G4Box("Solid world", 0.2*m, 0.2*m, 0.2*m);
    G4LogicalVolume * logicWorld = new G4LogicalVolume(solidWorld, worldMat, "Logic world");
    G4VPhysicalVolume * physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "Physical world", 0, false, 0, false);

    // Outern cylinder
    G4Tubs * solidCyl_o = new G4Tubs("Solid outern cylinder", 0.*mm, 53*mm, 55*mm, 0, twopi);
    G4LogicalVolume * logicCyl_o = new G4LogicalVolume(solidCyl_o, inox, "Logic outern cylinder");
    G4VPhysicalVolume * physCyl_o = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCyl_o, "Physical outern cylinder", logicWorld, false, 0, false);
    
    logicCyl_o->SetVisAttributes(cGrey);
    
    // Vacuum cylinder
    G4Tubs * solidCyl_v = new G4Tubs("Solid vacuum cylinder", 0.*mm, 50*mm, 54.5*mm, 0, twopi);
    G4LogicalVolume * logicCyl_v = new G4LogicalVolume(solidCyl_v, vacuum, "Logic vacuum cylinder");
    G4VPhysicalVolume * physCyl_v = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCyl_v, "Physical vacuum cylinder", logicCyl_o, false, 0, false);

    logicCyl_v->SetVisAttributes(cGrey);

    // Inner cylinder
    G4Tubs * solidCyl_i = new G4Tubs("Solid inner cylinder", 0.*mm, 30*mm, 35*mm, 0, twopi);
    G4LogicalVolume * logicCyl_i = new G4LogicalVolume(solidCyl_i, inox, "Logic inner cylinder");
    G4VPhysicalVolume * physCyl_i = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCyl_i, "Physical inner cylinder", logicCyl_v, false, 0, false);
    
    logicCyl_i->SetVisAttributes(cWhite);

    // LH2 cylinder
    G4Tubs * solidLH2 = new G4Tubs("Solid LH2 cylinder", 0.*mm, 29.5*mm, 34.5*mm, 0, twopi);
    G4LogicalVolume * logicLH2 = new G4LogicalVolume(solidLH2, lH2, "Logic LH2 cylinder");
    G4VPhysicalVolume * physLH2 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicLH2, "Physical LH2 cylinder", logicCyl_i, false, 0, false);
    
    logicLH2->SetVisAttributes(cWhite);

    return physWorld;
}