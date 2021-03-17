#include "TestPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TestProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"



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
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATestPlayer::HandleMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATestPlayer::HandleMoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ATestPlayer::HandleLookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATestPlayer::HandleLookUp);


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

void ATestPlayer::HandleShoot()
{
	UE_LOG(LogTemp, Log, TEXT("pew pew"));
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Camera->GetComponentLocation() + Camera->GetForwardVector() * 80);
	SpawnTransform.SetRotation(Camera->GetComponentRotation().Quaternion());
	GetWorld()->SpawnActor<ATestProjectile>(ProjectileClass, SpawnTransform);
}

void ATestPlayer::HandleWeaponSwap(float value)
{
	SelectedWeapon = value;
}
