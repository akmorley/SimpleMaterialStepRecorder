#
# This is based on Tracking/TrkG4Components/TrkG4UserActions/share/GeantinoMapping_jobOptions.py
# Copied 11/04/2018
# Updated 22/09/2020
#


#==============================================================
#
#
#		This job option runs the G4 simulation
#		of the ATLAS detector and the GeantinoMapping.
#		It can be run using athena.py
#

#--- Algorithm sequence ---------------------------------------
from AthenaCommon.AlgSequence import AlgSequence
topSeq = AlgSequence()

#--- Output threshold (DEBUG, INFO, WARNING, ERROR, FATAL) ----
from AthenaCommon.AppMgr import ServiceMgr
from AthenaCommon.Constants import VERBOSE, INFO
ServiceMgr.MessageSvc.OutputLevel  = INFO
ServiceMgr.MessageSvc.defaultLimit = 10000

#--- Detector flags -------------------------------------------
from AthenaCommon.DetFlags import DetFlags
from AthenaCommon.GlobalFlags import globalflags

import random
import time

### pass arguments with athena -c "..." ...jobOptions.py:
if 'myMomentum' not in dir() :
    myMomentum = 100000

if 'myRandomOffset' not in dir() :
    myRandomOffset = int(random.uniform(0,time.time())*0.001 )

if 'myRandomSeed1' not in dir() :
    myRandomSeed1 = int(random.uniform(0,time.time()))

if 'myRandomSeed2' not in dir() :
    myRandomSeed2 = int(random.uniform(0,time.time()))

if 'myMaxEvent' not in dir() :
    myMaxEvent = 100

if 'myGeo' not in dir() :
    myGeo = 'ATLAS-R2-2016-00-00-00'

print('Random seeds and offset as calcluated by jobOptions ', myRandomSeed1, ' ', myRandomSeed2, ' offset - ', myRandomOffset)


# Set everything to ATLAS
DetFlags.ID_setOn()
DetFlags.Calo_setOn()
DetFlags.Muon_setOff()
# the global flags
globalflags.ConditionsTag = 'OFLCOND-SIM-00-00-00'
print(globalflags.ConditionsTag)


#--- AthenaCommon flags ---------------------------------------
from AthenaCommon.AthenaCommonFlags import athenaCommonFlags
athenaCommonFlags.PoolEvgenInput.set_Off()   ### is this necessary?
athenaCommonFlags.PoolHitsOutput = 'Hits.pool.root'
athenaCommonFlags.EvtMax = myMaxEvent

#--- Simulation flags -----------------------------------------
from G4AtlasApps.SimFlags import simFlags
simFlags.load_atlas_flags() # Going to use an ATLAS layout
simFlags.SimLayout = myGeo
simFlags.RunNumber = 284500 # MC16a run number used for all Run2 simulation
simFlags.EventFilter.set_Off()


myMinEta = -3.0
myMaxEta =  3.0

myPDG    = 999   # 999 = Geantinos, 13 = Muons

include("GeneratorUtils/StdEvgenSetup.py")
theApp.EvtMax = 1000

import ParticleGun as PG
pg = PG.ParticleGun()
pg.sampler.pid = 999
pg.randomSeed = 123456
pg.sampler.mom = PG.EEtaMPhiSampler(energy=myMomentum, eta=[myMinEta,myMaxEta])
topSeq += pg

simFlags.RandomSeedOffset = myRandomOffset
simFlags.RandomSeedList.addSeed( "SINGLE", myRandomSeed1, myRandomSeed2 )

from RngComps.RngCompsConf import AtRndmGenSvc
myAtRndmGenSvc = AtRndmGenSvc()
myAtRndmGenSvc.Seeds = ["SINGLE "+str(myRandomSeed1)+" "+str(myRandomSeed2) ]
myAtRndmGenSvc.OutputLevel 	= DEBUG
myAtRndmGenSvc.EventReseeding   = False
ServiceMgr += myAtRndmGenSvc

# add the material step recording action

simFlags.OptionalUserActionList.addAction('G4UA::MaterialStepRecorderTool')
simFlags.OptionalUserActionList.addAction('SimpleStepRecorderTool')


############### The Material hit collection ##################

from AthenaPoolCnvSvc.WriteAthenaPool import AthenaPoolOutputStream
# --- commit interval (test)
ServiceMgr.AthenaPoolCnvSvc.OutputLevel = DEBUG
MaterialStream              = AthenaPoolOutputStream ( 'MaterialStream' )
MaterialStream.OutputFile   =   "MaterialStepFile.root"
MaterialStream.ItemList    += [ 'Trk::MaterialStepCollection#*']

##############################################################

include("G4AtlasApps/G4Atlas.flat.configuration.py")

# Add the beam effects algorithm
from AthenaCommon.CfgGetter import getAlgorithm
topSeq += getAlgorithm("BeamEffectsAlg", tryDefaultConfigurable=True)

from AthenaCommon.CfgGetter import getPublicTool
topSeq.BeamEffectsAlg.GenEventManipulators = [getPublicTool("GenEventValidityChecker")]

# Populate alg sequence
topSeq += getAlgorithm("G4AtlasAlg",tryDefaultConfigurable=True)

# Conditions sequence for Athena MT
from AthenaCommon.AlgSequence import AthSequencer
condSeq = AthSequencer("AthCondSeq")
if not hasattr(condSeq, "BeamSpotCondAlg"):
   from BeamSpotConditions.BeamSpotConditionsConf import BeamSpotCondAlg
   condSeq += BeamSpotCondAlg( "BeamSpotCondAlg" )


#--- End jobOptions.GeantinoMapping.py file  ------------------------------
