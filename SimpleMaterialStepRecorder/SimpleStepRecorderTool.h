#ifndef SIMPLESTEPRECORDERTOOL_H
#define SIMPLESTEPRECORDERTOOL_H

// Infrastructure includes
#include "G4AtlasTools/UserActionToolBase.h"

// Local includes
#include "SimpleMaterialStepRecorder/MaterialStepRecorder.h"



/// @class SimpleStepRecorderTool
/// @brief Tool which manages the MaterialStepRecorder action
///

class SimpleStepRecorderTool : public G4UA::UserActionToolBase<MaterialStepRecorder>
{

public:
  /// Standard constructor
  SimpleStepRecorderTool(const std::string& type, const std::string& name,const IInterface* parent);
protected:
  /// Create an action for this thread
  virtual std::unique_ptr<MaterialStepRecorder>
  makeAndFillAction( G4UA::G4AtlasUserActions&) override final;
}; // class SimpleStepRecorderTool


#endif