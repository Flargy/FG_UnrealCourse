#pragma once
#include "GameFramework/Actor.h"
#include "TestProjectileV2.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ATestProjectileV2 : public AActor
{
	GENERATED_BODY()

public:
	ATestProjectileV2();

	void BeginPlay();
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void Explode(const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	FVector Velocity;
};