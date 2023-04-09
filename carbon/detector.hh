#ifndef DETECTOR_HH
#define DETECTOR_HH
#include "G4VSensitiveDetector.hh"
#include "g4root_defs.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
class SensDetector : public G4VSensitiveDetector{
public:
	SensDetector(G4String);
	~SensDetector();
	
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};
#endif
