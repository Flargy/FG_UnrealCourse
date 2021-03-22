#pragma once
#include "GameFramework/Actor.h"
#include "StationaryEnemy.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class AStationaryEnemy : public AActor
{
	GENERATED_BODY()
public:
	AStationaryEnemy();


	UPROPERTY(EditDefaultsOnly)
		UCapsuleComponent* Body;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Gun1Mesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Gun2Mesh;

	
	UPROPERTY()
		float RotationSpeed = 60.f;
	UPROPERTY()
		float RotationDegrees = 80.f;
	UPROPERTY()
		float TargetUpdateFrequency = 1.f;
	UPROPERTY()
		float FireFrequency = 0.2f;

	AActor* Target;
};