// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstCourseGameModeBase.h"
#include "Player/TestPlayer.h"

AFirstCourseGameModeBase::AFirstCourseGameModeBase()
{
	DefaultPawnClass = ATestPlayer::StaticClass(); // sets this as the default player when starting
}
