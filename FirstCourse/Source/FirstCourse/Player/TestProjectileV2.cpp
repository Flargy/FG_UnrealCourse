#include "TestProjectileV2.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


ATestProjectileV2::ATestProjectileV2()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Sphere;

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

}
