#pragma once
#include "Components/ActorComponent.h"
#include "ProjectileResponseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestProjectileOnHitEvent);


UCLASS(Meta = (BlueprintSpawnableComponent))
class UProjectileResponseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UProjectileResponseComponent();

	UPROPERTY(BlueprintAssignable)
	FTestProjectileOnHitEvent OnProjectileHit;
};

// Events for things to happen when shot