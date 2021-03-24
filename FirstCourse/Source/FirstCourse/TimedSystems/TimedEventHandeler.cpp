#include "TimedEventHandeler.h"

void ATimedEventHandeler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeCounter += DeltaTime;

	if (TimeCounter >= EventTimeIntervall)
	{
		TimeCounter = 0;
		OnTimedEvent();
	}
}
