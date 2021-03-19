#include "GunGun.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TestProjectileV2.h"

AGunGun::AGunGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box1"));
	RootComponent = Box1;

	Box2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box2"));
	Box2->SetupAttachment(RootComponent);

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Mesh1->SetupAttachment(RootComponent);

	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Mesh2->SetupAttachment(RootComponent);

	FireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FireLocation"));
	FireLocation->SetupAttachment(RootComponent);
}


void AGunGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGunGun::Tick(float DeltaTime)
{
	
	ShotTimer += DeltaTime;
	if (ShotTimer >= ShotInterval)
	{
		Explode();
		if (AmmoCapacity <= 0)
		{
			Destroy();
			return;
		}
		AmmoCapacity--;
		FTransform ImpulseLocation = FireLocation->GetComponentTransform();
		ShotTimer = 0;
		if (SweetChristDontSetMeToTrue == false || AmmoCapacity == 0)
		{
			ATestProjectileV2* projectile = GetWorld()->SpawnActor<ATestProjectileV2>(Ammo, ImpulseLocation);
			projectile->SetSpawnImpulse(ImpulseLocation.GetLocation() - GetActorForwardVector() * 10);
			Box1->AddRadialImpulse(ImpulseLocation.GetLocation(), 150.f, 150000.f, ERadialImpulseFalloff::RIF_Linear);
			projectile->SetActorScale3D(GetActorScale3D());
			return;
		}

		
		FVector SmallerScale = GetActorScale3D() * 0.5f;
		AGunGun* OhGodNo = GetWorld()->SpawnActor<AGunGun>(AMistake, ImpulseLocation);
		OhGodNo->Initialize(AmmoCapacity);
		OhGodNo->SetSpawnImpulse(ImpulseLocation.GetLocation() - GetActorForwardVector() * 10);
		Box1->AddRadialImpulse(ImpulseLocation.GetLocation(), 150.f, 150000.f, ERadialImpulseFalloff::RIF_Linear);

		
		OhGodNo->SetActorScale3D(SmallerScale);

	}
}

void AGunGun::SetSpawnImpulse(FVector location)
{
	Box1->AddRadialImpulse(location, 100.f, 50000.f, ERadialImpulseFalloff::RIF_Constant);

}

void AGunGun::Initialize(int Counter)
{
	AmmoCapacity = Counter;
}
