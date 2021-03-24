#pragma once
#include "GameFramework/Actor.h"
#include "TimedEventHandeler.generated.h"

UCLASS()
class ATimedEventHandeler : public AActor
{
	GENERATED_BODY()

public:
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
		void OnTimedEvent();

private:
	UPROPERTY(EditDefaultsOnly)
		float EventTimeIntervall = 5.f;
	float TimeCounter = 0.f;
};