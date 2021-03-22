#pragma once
#include "GameFramework/Actor.h"
#include "PatrolEnemy.generated.h"

class USceneComponent;
class UBoxComponent;
class USphereComponent;
class UStaticMeshComponent;
class ATargetPoint;

UCLASS()
class APatrolEnemy : public AActor
{
	GENERATED_BODY()

public:
	APatrolEnemy();
	void BeginPlay();
	void Tick(float DeltaTime);


	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> PatrolPoints;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* KillZone;

private:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5.f;
	float AccuracyOffset = 0.2f;
	float AimTime = 2.f;
	float TimeSpentAiming = 0.f;
	float RotationSpeed = 70.f;
	bool FutureLocationAproximation = false;
	bool TargetInRange = false;
	int PatrolIndex = 0;
	ATargetPoint* CurrentPoint;
	AActor* Target;

	UFUNCTION()
		void EnterOverlap(UPrimitiveComponent* MyComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep,
			const FHitResult& SweepHit);

	UFUNCTION()
		void ExitOverlap(UPrimitiveComponent* MyComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 BodyIndex);

	void SelectNextPatrolPoint();

	void AimAtTarget(float DeltaTime);

	void MoveToPatrolPoint(float DeltaTime);
};
