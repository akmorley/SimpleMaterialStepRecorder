

#include "SimpleMaterialStepRecorder/SimpleStepRecorderTool.h"


SimpleStepRecorderTool::SimpleStepRecorderTool(const std::string& type,
                                              const std::string& name,
                                              const IInterface* parent)
  : G4UA::UserActionToolBase<MaterialStepRecorder>(type, name, parent)
{
}

std::unique_ptr<MaterialStepRecorder>
SimpleStepRecorderTool::makeAndFillAction( G4UA::G4AtlasUserActions& actionList)
{
  ATH_MSG_DEBUG("Constructing a MaterialStepRecorder action");
  auto action = std::make_unique<MaterialStepRecorder>();
  actionList.runActions.push_back( action.get() );
  actionList.eventActions.push_back( action.get() );
  actionList.steppingActions.push_back( action.get() );
  return action;
}

