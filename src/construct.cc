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

    G4VisAttributes * cGreen = new G4VisAttributes(G4Colour(0, 1, 0));
    cGreen->SetForceWireframe(true);

    G4VisAttributes * cBlue = new G4VisAttributes(G4Colour(0, 0, 1));
    cBlue->SetForceWireframe(true);

    G4VisAttributes * cCyan_l = new G4VisAttributes(G4Colour(0, 1, 0.93));
    cCyan_l->SetForceWireframe(true);

    G4VisAttributes * cYellow = new G4VisAttributes(G4Colour(1, 1, 0));
    cYellow->SetForceWireframe(true);

    // ---------- MATERIALS -------------------------------

    G4Material * worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4Material * lH2 = new G4Material("Liquid hidrogen", density = 0.07085*g/cm3, 1, kStateLiquid);
    lH2->AddElement(nist->FindOrBuildElement("H"), 2);

    G4Material * inox = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

    G4Material * vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    // ---------- OBJECTS ---------------------------------

    // World
    G4Box * solidWorld = new G4Box("solidWorld", 0.2*m, 0.2*m, 0.2*m);
    G4LogicalVolume * logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume * physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicWorld, "physWorld", 0, false, 0, false);

    // Outern cylinder
    G4Tubs * solidCyl_o = new G4Tubs("solidCyl_o", 0.*mm, 53*mm, 55*mm, 0, twopi);
    G4LogicalVolume * logicCyl_o = new G4LogicalVolume(solidCyl_o, inox, "logicCyl_o");
    G4VPhysicalVolume * physCyl_o = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCyl_o, "physCyl_o", logicWorld, false, 0, true);

    logicCyl_o->SetVisAttributes(cGrey);

    // Vacuum cylinder
    G4Tubs * solidCyl_v = new G4Tubs("solidCyl_v", 0.*mm, 50*mm, 54.5*mm, 0, twopi);
    G4LogicalVolume * logicCyl_v = new G4LogicalVolume(solidCyl_v, vacuum, "logicCyl_v");
    G4VPhysicalVolume * physCyl_v = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCyl_v, "physCyl_v", logicCyl_o, false, 0, true);

    logicCyl_v->SetVisAttributes(cGrey);

    // Inner cylinder
    G4Tubs * solidCyl_i = new G4Tubs("solidCyl_i", 0.*mm, 30*mm, 35*mm, 0, twopi);
    G4LogicalVolume * logicCyl_i = new G4LogicalVolume(solidCyl_i, inox, "logicCyl_i");
    G4VPhysicalVolume * physCyl_i = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCyl_i, "physCyl_i", logicCyl_v, false, 0, true);

    logicCyl_i->SetVisAttributes(cCyan_l);

    // LH2 cylinder
    G4Tubs * solidLH2 = new G4Tubs("solidLH2", 0.*mm, 29.5*mm, 34.5*mm, 0, twopi);
    logicLH2 = new G4LogicalVolume(solidLH2, lH2, "logicLH2");
    G4VPhysicalVolume * physLH2 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicLH2, "physLH2", logicCyl_i, false, 0, true);

    logicLH2->SetVisAttributes(cCyan_l);

    // First detector (FDet)
    G4Tubs * solidFDet = new G4Tubs("solidFDet", 0.*mm, 49.9*mm, 0.5*mm, 0, twopi);
    logicFDet = new G4LogicalVolume(solidFDet, vacuum, "logicFDet");
    G4VPhysicalVolume * physFDet = new G4PVPlacement(0, G4ThreeVector(0, 0, -54*mm), logicFDet, "physFDet", logicCyl_v, false, 0, true);  

    logicFDet->SetVisAttributes(cYellow);

    // Modulable thickness layer
    double thick = 0.05;
    G4Tubs * solidThick = new G4Tubs("solidThick", 0.*mm, 53.*mm, (thick/2)*mm, 0, twopi);
    G4LogicalVolume * logicThick = new G4LogicalVolume(solidThick, inox, "logicThick");

    int Layers = 20;
    for(int i=0; i<Layers; i++){
        G4VPhysicalVolume * physThick = new G4PVPlacement(0, G4ThreeVector(0, 0, (-55 - thick/2 - thick*i)*mm), logicThick, "physThick", logicWorld, false, i, true);
    }

    logicThick->SetVisAttributes(cGreen);

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    // ----------- FILTERS --------------------------------

    // Pi- filter
    MySDParticleFilter * piFilter = new MySDParticleFilter("piFilter", "pi-");

    // ----------- ACTIVE DETECTORS -----------------------

    // First detector (FDet): study pi- momentum after entering the vacuum volume
    MySensitiveDetector * sensFDet = new MySensitiveDetector("sensFDet");
    sensFDet->SetFilter(piFilter);               // added filter
    logicFDet->SetSensitiveDetector(sensFDet);   // setted

    // LH2 detector (LH2Det): study of pi- CEX in LH2 target
    MySensitiveDetector * sensLH2 = new MySensitiveDetector("sensLH2");
    sensLH2->SetFilter(piFilter);               // added filter
    logicLH2->SetSensitiveDetector(sensLH2);    // setted

}