#include "TestPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TestProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GunGun.h"



ATestPlayer::ATestPlayer()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());

	auto* MoveComp = GetCharacterMovement();
	MoveComp->JumpZVelocity = 700.f;

	JumpMaxCount = 2;
}

void ATestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ATestPlayer::HandleJumpInput );
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ATestPlayer::HandleShoot);
	PlayerInputComponent->BindAction(TEXT("Weapon1"), EInputEvent::IE_Pressed, this, &ATestPlayer::SelectWeapon1);
	PlayerInputComponent->BindAction(TEXT("Weapon2"), EInputEvent::IE_Pressed, this, &ATestPlayer::SelectWeapon2);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATestPlayer::HandleMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATestPlayer::HandleMoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ATestPlayer::HandleLookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATestPlayer::HandleLookUp);


}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	//Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
}

void ATestPlayer::HandleJumpInput()
{
	Jump();
}

void ATestPlayer::HandleMoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);

}

void ATestPlayer::HandleMoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void ATestPlayer::HandleLookRight(float value)
{
	AddControllerYawInput(value);
}

void ATestPlayer::HandleLookUp(float value)
{
	AddControllerPitchInput(value);
}

void ATestPlayer::HandleWeaponSwap(int value)
{
	UE_LOG(LogTemp, Log, TEXT("swapping values"));
	SelectedWeapon = value;
}

void ATestPlayer::SelectWeapon1()
{
	HandleWeaponSwap(0);
}

void ATestPlayer::SelectWeapon2()
{
	HandleWeaponSwap(1);
}

void ATestPlayer::HandleShoot()
{

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Camera->GetComponentLocation() + Camera->GetForwardVector() * 80);
	SpawnTransform.SetRotation(Camera->GetComponentRotation().Quaternion());

	switch (SelectedWeapon)
	{
	case 0:
		UE_LOG(LogTemp, Log, TEXT("shooting projectile"));
		GetWorld()->SpawnActor<ATestProjectile>(ProjectileClass, SpawnTransform);
		break;
	case 1:
		UE_LOG(LogTemp, Log, TEXT("shooting gun gun"));
		AGunGun* GunInstance = GetWorld()->SpawnActor<AGunGun>(GunGunClass, SpawnTransform);
		GunInstance->SetSpawnImpulse(SpawnTransform.GetLocation() - GunInstance->GetActorForwardVector() * 60.f + GunInstance->GetActorUpVector() *8.f);
		break;

	}
}


