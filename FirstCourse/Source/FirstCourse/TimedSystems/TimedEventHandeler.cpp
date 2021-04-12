#include "TimedEventHandeler.h"

ATimedEventHandeler::ATimedEventHandeler()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimedEventHandeler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeCounter += DeltaTime;

	if (TimeCounter >= EventTimeIntervall)
	{
		UE_LOG(LogTemp, Log, TEXT("Triggering even now"))
		TimeCounter = 0;
		OnTimedEvent();
	}
}
