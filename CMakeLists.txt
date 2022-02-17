
# Declare the package name:
atlas_subdir( SimpleMaterialStepRecorder  )

# External dependencies:
find_package( CLHEP )
find_package( Geant4 )
find_package( ROOT COMPONENTS Core Tree TFile )

# Component(s) in the package:
atlas_add_library( SimpleMaterialStepRecorder
                  SimpleMaterialStepRecorder/*.h
                  src/*.cxx
                  src/components/*.cxx
                  PUBLIC_HEADERS SimpleMaterialStepRecorder
                  INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${GEANT4_INCLUDE_DIRS} ${CLHEP_INCLUDE_DIRS}
                  LINK_LIBRARIES ${ROOT_LIBRARIES} ${GEANT4_LIBRARIES} ${CLHEP_LIBRARIES} AthenaBaseComps GaudiKernel G4AtlasToolsLib TrkDetDescrInterfaces TrkGeometry TrkMaterialOnTrack TrkParameters CxxUtils StoreGateLib GeoPrimitives SimHelpers TrkSurfaces TrkExInterfaces TrkExUtils TrkValInterfaces )

# Install files from the package:
atlas_install_joboptions( share/*.py )


atlas_add_executable( MaterialMap
          util/MaterialMap.cxx util/Reader.C
          INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
          LINK_LIBRARIES ${ROOT_LIBRARIES} 
          SimpleMaterialStepRecorder )
