/**
 * @file DetectorConstruction.hh
 * @author Nicholas Carrara [nmcarrara@ucdavis.edu]
 * @brief 
 * @version 0.0
 * @details 
 *  Change log:
 *      2022/09/20 - Initial creation of the file.
 * @date 2022-09-23
 */
#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SubtractionSolid.hh"
#include "G4Material.hh"
#include "G4SDManager.hh"
#include "G4Cache.hh"
#include "G4AutoDelete.hh"

#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4GDMLParser.hh"

#include "yaml-cpp/yaml.h"

#include "EAR1.hh"
#include "EAR2.hh"
#include "LiG.hh"
#include "Material.hh"
#include "SimpleDetector.hh"
#include "Target.hh"

namespace marex
{
    class DetectorConstruction : public G4VUserDetectorConstruction
    {
    public:
        DetectorConstruction();
        ~DetectorConstruction();

        DetectorConstruction(YAML::Node config);

        void DefineMaterials();

        virtual G4VPhysicalVolume* Construct();
    
    private:
        virtual void ConstructSDandField();

    private:
        G4String mWorldMaterialName = {"high_vacuum"};
        G4double mExperimentalHallX = {500 * m};
        G4double mExperimentalHallY = {500 * m};
        G4double mExperimentalHallZ = {500 * m};

        // Experimental Hall
        G4Material *mWorldMaterial;
        G4Box* mSolidExperimentalHall;
        G4LogicalVolume* mLogicalExperimentalHall;
        G4VPhysicalVolume* mPhysicalExperimentalHall;

        // EAR1 mEAR1;
        // Target mTarget;
        // SimpleDetector mSimpleDetector;

        YAML::Node mConfig;
    };
}