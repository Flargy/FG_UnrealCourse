#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyHealthOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTCOURSE_API UEnemyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void TakeDamage(float Damage);

	UPROPERTY(BlueprintAssignable)
	FEnemyHealthOnDeath OnDeath;

protected:	
	float Health = 4;
		
};
