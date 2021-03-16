#pragma once
#include "GameFramework/Actor.h"
#include "TestProjectile.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ATestProjectile : public AActor
{
	GENERATED_BODY()

public:
	ATestProjectile();

	void Tick(float DeltaTime);
	void BeginPlay();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	FVector Velocity;
};