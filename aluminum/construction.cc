#include "construction.hh"

NewDetec::NewDetec()
{
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

	fMessenger->DeclareProperty("nCols", nCols, "Number of columns");
	fMessenger->DeclareProperty("nRows", nRows, "Number of rows");

	nCols = 100;
	nRows = 100;

	DefineMaterials();
}

NewDetec::~NewDetec()
{}

void NewDetec::DefineMaterials(){
	G4NistManager *nist = G4NistManager::Instance();
	worldMat = nist->FindOrBuildMaterial("G4_AIR");


	Al = nist->FindOrBuildElement("Al");

	Aluminium = new G4Material("Aluminium", 2.7*g/cm3, 1);
	Aluminium->AddElement(Al, 100*perCent);
	
	G4double energy[2] = {1.239841939*eV/1000000000, 1.239841939*eV/0.7};

	G4double rindexWorld[2] = {1.0, 1.0};
	G4double rindexAluminium[2] = {1.01, 1.3};

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

	G4MaterialPropertiesTable *mptAluminium = new G4MaterialPropertiesTable();
	mptAluminium->AddProperty("RINDEX", energy, rindexAluminium, 2);


	worldMat->SetMaterialPropertiesTable(mptWorld);
	Aluminium->SetMaterialPropertiesTable(mptAluminium);
}

G4VPhysicalVolume *NewDetec::Construct(){
	G4double xWorld = 0.5*m;
	G4double yWorld = 0.5*m;
	G4double zWorld = 0.5*m;
	
	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
	logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.0005*m);
	logicRadiator = new G4LogicalVolume(solidRadiator, Aluminium, "logicRadiator");
	fScoringVolume = logicRadiator;
	physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
	solidDetector = new G4Box("solidDetector", xWorld/nRows, yWorld/nCols, 0.01*m);
	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
	
	for (G4int i = 0; i < nRows; i++){
		for (G4int j = 0; j < nCols; j++){
			physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/nRows, -0.5*m+(j+0.5)*m/nCols, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*nCols, true);
			}
	}
	
	return physWorld;
}

void NewDetec::ConstructSDandField()
{
	SensDetector *sensDet = new SensDetector("SensitiveDetector");
	logicDetector->SetSensitiveDetector(sensDet);
}











