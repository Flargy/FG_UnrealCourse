#include "PatrolEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "FirstCourse/Player/TestPlayer.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"


APatrolEnemy::APatrolEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	RootComponent = Box;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	KillZone = CreateDefaultSubobject<USphereComponent>(TEXT("KillZone"));
	KillZone->SetupAttachment(RootComponent);
	KillZone->OnComponentBeginOverlap.AddDynamic(this, &APatrolEnemy::EnterOverlap);
	KillZone->OnComponentEndOverlap.AddDynamic(this, &APatrolEnemy::ExitOverlap);

}

void APatrolEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentPoint = PatrolPoints[PatrolIndex];
}

void APatrolEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (TargetInRange)
	{
		AimAtTarget(DeltaTime);
		return;
	}
	MoveToPatrolPoint(DeltaTime);

}

void APatrolEnemy::EnterOverlap(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	if (OtherActor->IsA(ATestPlayer::StaticClass()))
	{
		Target = OtherActor;
		TargetInRange = true;
	}
}

void APatrolEnemy::ExitOverlap(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex)
{
	if (OtherActor->IsA(ATestPlayer::StaticClass()))
	{
		TargetInRange = false;
	}
}

void APatrolEnemy::SelectNextPatrolPoint()
{
	PatrolIndex = (PatrolIndex + 1) % PatrolPoints.Num();
	CurrentPoint = PatrolPoints[PatrolIndex];
}

void APatrolEnemy::AimAtTarget(float DeltaTime)
{
	FVector Direction = Target->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	FRotator RotationToTarget = UKismetMathLibrary::MakeRotFromX(Direction);
	FRotator RotationPiece = UKismetMathLibrary::RInterpTo_Constant(GetActorRotation(), RotationToTarget, DeltaTime, RotationSpeed);
	RotationPiece.Pitch = UKismetMathLibrary::ClampAngle(RotationPiece.Pitch, -45, 70);
	SetActorRotation(RotationPiece);

	float AimPrecision = FVector::DotProduct(Direction, GetActorForwardVector());

	if (AimPrecision >= 1 - AccuracyOffset)
	{
		TimeSpentAiming += DeltaTime;
	}

	if (TimeSpentAiming >= AimTime)
	{
		UE_LOG(LogTemp, Log, TEXT("pew pew"));
		TimeSpentAiming = 0.f;
	}
}

void APatrolEnemy::MoveToPatrolPoint(float DeltaTime)
{
	TimeSpentAiming = 0;

	FVector Direction = CurrentPoint->GetActorLocation() - GetActorLocation();
	Direction.Normalize();

	AddActorWorldOffset(Direction * DeltaTime * MoveSpeed);
	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Direction);
	SetActorRotation(Rotation);

	if (FVector::Distance(GetActorLocation(), CurrentPoint->GetActorLocation()) < 50.f)
	{
		SelectNextPatrolPoint();
	}
}
