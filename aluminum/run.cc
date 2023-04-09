#include "run.hh"

RunAction::RunAction(){
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->CreateNtuple("Hits", "Hits");
	manager->CreateNtupleIColumn("fEvent");
	manager->CreateNtupleDColumn("fX");
	manager->CreateNtupleDColumn("fY");
	manager->CreateNtupleDColumn("fZ");
	manager->FinishNtuple(0);

	manager->CreateNtuple("Scoring", "Scoring");
	manager->CreateNtupleDColumn("fEdep");
	manager->FinishNtuple(1);
}

RunAction::~RunAction(){}

void RunAction::BeginOfRunAction(const G4Run* run){
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	G4int runID = run->GetRunID();

	std::stringstream strRunID;
	strRunID << runID;

	manager->OpenFile("output"+strRunID.str()+".root");
}
void RunAction::EndOfRunAction(const G4Run*){
	G4AnalysisManager *manager = G4AnalysisManager::Instance();
	manager->Write();
	manager->CloseFile();
}