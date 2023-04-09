#include "stepping.hh"
#include "construction.hh"
#include "bits/stdc++.h"

SteppingAction::SteppingAction(EventAction *eventAction){
	fEventAction = eventAction;
}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step *step){
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

	const NewDetec *detectorConstruction = static_cast<const NewDetec*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	G4LogicalVolume *fScoringVolume = detectorConstruction -> fScoringVolume;

	if(volume != fScoringVolume)
		return;

	G4double edep = step->GetTotalEnergyDeposit();
	fEventAction->AddEdep(edep);
}