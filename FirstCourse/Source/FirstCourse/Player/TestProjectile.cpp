#include "TestProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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
		OnExplode(Hit);
		
		TArray<UPrimitiveComponent*> OverlappedComponents;

		UKismetSystemLibrary::SphereOverlapComponents(this, GetActorLocation(), 200.f, 
			ExplosionOverlapTypes, UPrimitiveComponent::StaticClass(), TArray<AActor*>(),
			OverlappedComponents);

		UKismetSystemLibrary::DrawDebugSphere(this, GetActorLocation(), 200.f, 12, 
			FLinearColor::Red, 5.f, 1.f);

		for (UPrimitiveComponent* Component : OverlappedComponents)
		{
			UE_LOG(LogTemp, Log, TEXT("Hitting actor '%s' :: '%s'"), *Component->GetOwner()->GetName(), *Component->GetName());
			Component->AddRadialImpulse(GetActorLocation(), 200.f, 200000.f, ERadialImpulseFalloff::RIF_Linear);
		}

		Destroy();
		return;
	}

	FRotator FacingRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
	SetActorRotation(FacingRotation);

}

