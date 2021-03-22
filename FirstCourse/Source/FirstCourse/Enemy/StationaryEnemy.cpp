#include "StationaryEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

AStationaryEnemy::AStationaryEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	RootComponent = Body;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);

	Gun1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun1"));
	Gun1Mesh->SetupAttachment(RootComponent);

	Gun2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun2"));
	Gun2Mesh->SetupAttachment(RootComponent);

}



