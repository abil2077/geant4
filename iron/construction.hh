#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "detector.hh"
#include "G4GenericMessenger.hh"

class NewDetec: public G4VUserDetectorConstruction
{
public: 
	NewDetec();
	~NewDetec();

	G4LogicalVolume *GetScoringVolume() const {
		return fScoringVolume;
	}

	virtual G4VPhysicalVolume *Construct();

public:
	G4LogicalVolume *logicDetector; 
	virtual void ConstructSDandField();
	G4int nCols, nRows;

	G4GenericMessenger *fMessenger;

	G4LogicalVolume *fScoringVolume;

	G4Box *solidWorld, *solidRadiator, *solidDetector;
	G4LogicalVolume *logicWorld, *logicRadiator;
	G4VPhysicalVolume *physWorld, *physRadiator, *physDetector;
	G4Material *worldMat, *Iron;
	G4Element *Fe;
	void DefineMaterials();
};





#endif
