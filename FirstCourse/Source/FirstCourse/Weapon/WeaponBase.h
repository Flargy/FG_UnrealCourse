#pragma once
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


UCLASS(Abstract) // makes it not show up in lists and cant be instantiated
class AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	virtual void Fire() {}
};