#pragma once
#include "WeaponBase.h"
#include "GrenadeLauncher.generated.h"

UCLASS()
class AGrenadeLauncher : public AWeaponBase
{
	GENERATED_BODY()

public:
	void Fire() override;
};