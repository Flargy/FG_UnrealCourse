#pragma once
#include "GameFramework/Character.h"
#include "TestPlayer.generated.h"

class ATestProjectile;
class UCameraComponent;
class AGunGun;

UCLASS()
class ATestPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ATestPlayer();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATestProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunGun> GunGunClass;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	int SelectedWeapon = 0;


private:
	void HandleJumpInput();
	void HandleShoot();
	void HandleMoveForward(float value);
	void HandleMoveRight(float value);
	void HandleLookRight(float value);
	void HandleLookUp(float value);

	void HandleWeaponSwap(int value);
	void SelectWeapon1();
	void SelectWeapon2();
};