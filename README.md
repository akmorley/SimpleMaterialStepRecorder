# SimpleMaterialStepRecorder

The jobOptions SimpleGeantinoMapping_jobOptions.py will create an Ntuple ("GeantinoNtuple.root") that stores each individual Step length, radiation and interaction length  and density of the material crossed and the position of the step.

The executable MaterialMap reads in this file/s and makes some pretty plots. To execute:
MaterialMap path/to/inputFiles/ outFileName.root

Another more standard output of the job is the "MaterialStepFile.root" file which stores a Trk::MaterialStepCollection. This can used to analyse the material but you will need to read it in Athena to do so.



