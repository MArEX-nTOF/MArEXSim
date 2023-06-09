/**
 * @file DetectorConstruction.cxx
 * @author Nicholas Carrara [nmcarrara@ucdavis.edu]
 * @brief 
 * @version 0.0
 * @details 
 *  Change log:
 *      2022/09/20 - Initial creation of the file.
 * @date 2022-09-23
 */
#include "DetectorConstruction.hh"

namespace marex
{
    DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
    {
        DefineMaterials();
    }

    DetectorConstruction::DetectorConstruction(YAML::Node config)
    : G4VUserDetectorConstruction()
    , mConfig(config)
    {

        if(mConfig["hall"]["world_material"])   { mWorldMaterialName = mConfig["hall"]["world_material"].as<std::string>(); }
        if(mConfig["hall"]["world_x"])          { mExperimentalHallX = mConfig["hall"]["world_x"].as<G4double>() * m; }
        if(mConfig["hall"]["world_y"])          { mExperimentalHallY = mConfig["hall"]["world_y"].as<G4double>() * m; }
        if(mConfig["hall"]["world_z"])          { mExperimentalHallZ = mConfig["hall"]["world_z"].as<G4double>() * m; }

        // mTarget = Target(config);
        // mDICER = DICER(config);
        // mnTOF = nTOF(config);

        DefineMaterials();
    }

    void DetectorConstruction::DefineMaterials()
    {
        mWorldMaterial = CreateMaterial(mWorldMaterialName, "World");
    }

    DetectorConstruction::~DetectorConstruction()
    {
    }

    G4VPhysicalVolume* DetectorConstruction::Construct()
    {
        DefineMaterials();
        // create the world volume
        mSolidExperimentalHall = new G4Box(
            "Solid_ArtieIExperimentalHall", 
            mExperimentalHallX, 
            mExperimentalHallY, 
            mExperimentalHallZ
        );
        mLogicalExperimentalHall = new G4LogicalVolume(
            mSolidExperimentalHall, 
            mWorldMaterial, 
            "Logical_ArtieIExperimentalHall"
        );
        mPhysicalExperimentalHall = new G4PVPlacement(
            0, 
            G4ThreeVector(0., 0., 0.),
            mLogicalExperimentalHall,
            "Physical_ArtieIExperimentalHall",
            0, 
            false,
            0
        );

        // if(mConfig["dicer"]) {
        //     mDICER.Construct(mLogicalExperimentalHall);
        // }
        // else {
        //     mnTOF.Construct(mLogicalExperimentalHall);
        // }

        // mTarget.Construct(mLogicalExperimentalHall);

        // if(mConfig["detector"]["detector_type"].as<std::string>() == "simple") {
        //     mSimpleDetector.Construct(mLogicalExperimentalHall);
        // }

        return mPhysicalExperimentalHall;
    }

    void DetectorConstruction::ConstructSDandField()
    {
    }
}