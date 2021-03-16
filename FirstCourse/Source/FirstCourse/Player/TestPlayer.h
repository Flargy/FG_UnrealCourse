#pragma once
#include "GameFramework/Character.h"
#include "TestPlayer.generated.h"

UCLASS()
class ATestPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ATestPlayer();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void HandleJumpInput();
	void HandleMoveForward(float value);
	void HandleMoveRight(float value);
	void HandleLookRight(float value);
	void HandleLookUp(float value);

};