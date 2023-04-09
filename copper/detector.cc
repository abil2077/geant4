#include "detector.hh"

SensDetector::SensDetector(G4String name) : G4VSensitiveDetector(name)
{}

SensDetector::~SensDetector(){}

G4bool SensDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *tracker = aStep->GetTrack();
	tracker->SetTrackStatus(fStopAndKill);

	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	G4cout << "Photon position: " << posPhoton << G4endl;
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4cout << "Detector " << copyNo << " position: " << posDetector << G4endl;

	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->FillNtupleIColumn(0, evt);
	manager->FillNtupleDColumn(1, posDetector[0]);
	manager->FillNtupleDColumn(2, posDetector[1]);
	manager->FillNtupleDColumn(3, posDetector[2]);
	manager->AddNtupleRow(0);
}
