#include "TestProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FirstCourse/Enemy/TestEnemy.h"
#include "ProjectileResponseComponent.h"


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
	Velocity = GetActorForwardVector() * 1500;
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

		TArray<AActor*> OverlappedActors;
		UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), 200.f, ExplosionOverlapTypes, ATestEnemy::StaticClass(), TArray<AActor*>(), OverlappedActors);

		for (auto* Enemy :OverlappedActors)
		{
			// If we hit enemy we cast the hit to an enemy
			/*ATestEnemy* HitEnemy = Cast<ATestEnemy>(Enemy);
			HitEnemy->Destroy();*/

			UProjectileResponseComponent* ResponseComp = Enemy->FindComponentByClass<UProjectileResponseComponent>();
			if (ResponseComp)
			{
				ResponseComp->OnProjectileHit.Broadcast();
			}
		}
		

		Destroy();
		return;
	}

	FRotator FacingRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
	SetActorRotation(FacingRotation);

}

