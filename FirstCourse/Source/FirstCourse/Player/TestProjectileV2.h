#pragma once
#include "GameFramework/Actor.h"
#include "TestProjectileV2.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class ATestProjectileV2 : public AActor
{
	GENERATED_BODY()

public:
	ATestProjectileV2();

	void BeginPlay();
	void Tick(float DeltaTime);

	UFUNCTION()
	void SetSpawnImpulse(FVector Location);

	UFUNCTION(BlueprintImplementableEvent)
	void Explode();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

	FVector Velocity;

	const float Lifespan = 3.f;
	float LifeTimer = 0.f;
};