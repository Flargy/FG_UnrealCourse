// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolActor.h"

// Sets default values
ACoolActor::ACoolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(RootComponent);
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ACoolActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Cool actor spawn"));
	
	Velocity = GetActorForwardVector() * speed;
}

// Called every frame
void ACoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Velocity -= FVector(0.f, 0.f, 900.f) * DeltaTime;
	FHitResult Hit;
	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);

	if (Hit.bBlockingHit)
	{
		Velocity = FMath::GetReflectionVector(Velocity, Hit.Normal);
	}
}

