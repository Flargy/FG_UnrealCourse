#include "TestEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "FirstCourse/Player/ProjectileResponseComponent.h"
#include "EnemyHealthComponent.h"

ATestEnemy::ATestEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	Response = CreateDefaultSubobject<UProjectileResponseComponent>(TEXT("ResponseComponent"));
	HealthComponent = CreateDefaultSubobject<UEnemyHealthComponent>(TEXT("HealthComponent"));
	//Response->OnProjectileHit.AddDynamic(this, classname::functionToBind);
	//HealthComponent->OnDeath.AddDynamic(this, &ATestEnemy::Die);
}

void ATestEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);

	FVector Direction = (Player->GetActorLocation() - GetActorLocation());
	Direction.Normalize();

	AddActorWorldOffset(Direction * DeltaTime * Speed);

	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Direction);

	SetActorRotation(Rotation);

}

void ATestEnemy::OnTakeDamage_Implementation()
{

}

void ATestEnemy::Die()
{
	Destroy();
}
