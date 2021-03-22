#pragma once
#include "GameFramework/Actor.h"
#include "GunGun.generated.h"

class ATestProjectileV2;
class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;

UCLASS()
class AGunGun : public AActor
{
	GENERATED_BODY()
	
public:
	AGunGun();


	void BeginPlay();
	void Tick(float DeltaTime);
	
	void SetSpawnImpulse(FVector location);
	void Initialize(int Counter);

	UFUNCTION(BlueprintImplementableEvent)
	void Explode();


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh1;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh2;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* FireLocation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATestProjectileV2> Ammo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunGun> AMistake;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box1;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Box2;

	float ShotInterval = 1.f;
	float ShotTimer = 0.f;
	int AmmoCapacity = 5;
	UPROPERTY(EditDefaultsOnly)
	bool SweetChristDontSetMeToTrue = false;
};