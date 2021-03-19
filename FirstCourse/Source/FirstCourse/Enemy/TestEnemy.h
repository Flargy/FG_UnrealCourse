#pragma once
#include "GameFramework/Actor.h"
#include "TestEnemy.generated.h"

class USphereComponent;
class UProjectileResponseComponent;

UCLASS()
class ATestEnemy : public AActor
{
	GENERATED_BODY()

public:
	ATestEnemy();

	void Tick(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
	void OnTakeDamage();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USphereComponent* Sphere;

	UPROPERTY(EditDefaultsOnly)
	UProjectileResponseComponent* Response;

	UPROPERTY(EditInstanceOnly)
	float Speed = 50.f;
};