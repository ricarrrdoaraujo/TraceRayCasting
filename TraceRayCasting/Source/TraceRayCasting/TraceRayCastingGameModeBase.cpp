// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "TraceRayCastingGameModeBase.h"
#include "RayCastPlayerController.h"

ATraceRayCastingGameModeBase::ATraceRayCastingGameModeBase()
{
	//Indica qual ser� a classe padr�o do PlayerController neste game mode
	PlayerControllerClass = ARayCastPlayerController::StaticClass();
}
