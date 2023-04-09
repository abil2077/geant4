#include "event.hh"

EventAction::EventAction(RunAction*){
	fEdep = 0.;
}

EventAction::~EventAction(){}

void EventAction::StartOfEventAction(const G4Event*){
	fEdep = 0.;
} 

void EventAction::EndOfEventAction(const G4Event*){
	G4cout << "Energy deposition: " << fEdep << " MeV" << G4endl;
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->FillNtupleDColumn(1, 0, fEdep);
	manager->AddNtupleRow(1);
}