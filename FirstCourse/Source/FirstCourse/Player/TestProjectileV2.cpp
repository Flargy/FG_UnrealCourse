#include "TestProjectileV2.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


ATestProjectileV2::ATestProjectileV2()
{
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetCollisionProfileName(TEXT("PhysicsActor"));
	RootComponent = Box;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetupAttachment(RootComponent);
}

void ATestProjectileV2::BeginPlay()
{
	Super::BeginPlay();
	Velocity = GetActorForwardVector() * 1000;
}

void ATestProjectileV2::Tick(float DeltaTime)
{
	LifeTimer += DeltaTime;

	if (LifeTimer >= Lifespan)
	{
		Explode();
		Destroy();
	}
}

void ATestProjectileV2::SetSpawnImpulse(FVector Location)
{
	Box->AddRadialImpulse(Location, 50.f, 9000.f, ERadialImpulseFalloff::RIF_Constant);
}
