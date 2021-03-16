#include "TestProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATestProjectile::ATestProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	
}

void ATestProjectile::BeginPlay()
{
	Super::BeginPlay();
	Velocity = GetActorForwardVector() * 1000;
}

void ATestProjectile::Tick(float DeltaTime)
{
	Velocity -= FVector(0.f, 0.f, 981.f) * DeltaTime;
	FHitResult Hit;
	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);

	if (Hit.bBlockingHit)
	{
		PrimaryActorTick.SetTickFunctionEnable(false);
	}

	FRotator FacingRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
	SetActorRotation(FacingRotation);

}

