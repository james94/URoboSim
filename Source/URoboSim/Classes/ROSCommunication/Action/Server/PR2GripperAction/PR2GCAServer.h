
#pragma once

#include "ROSCommunication/Action/Server/RActionServer.h"
#include "PR2GCAServer.generated.h"

UCLASS(Blueprintable, DefaultToInstanced, collapsecategories, hidecategories = Object, editinlinenew)
class UROBOSIM_API URGripperCommandActionServer : public URActionServer
{
  GENERATED_BODY()

public:

    URGripperCommandActionServer();

};
