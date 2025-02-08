// Nicholas Wile 2025 - Freely use this code for any purpose.


#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCam"));
	check(FPSCamera != nullptr);
	FPSCamera->SetupAttachment(CastChecked<USceneComponent>(GetCapsuleComponent()));
	FPSCamera->SetRelativeLocation(CameraPos);
	FPSCamera->bUsePawnControlRotation = true;

	// Create a mesh that is only visible to this player (viewed in first person)
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	check(FPSMesh != nullptr);
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCamera);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Player can't see third person mesh
	GetMesh()->SetOwnerNoSee(true);

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, "Controlling FPS Character");
	
	SetActorLocation(SpawnLocation);
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_zoomScale += (_isZooming ? DeltaTime/ZoomSpeed.X : -1 * DeltaTime/ZoomSpeed.Y);
	_zoomScale = FMath::Clamp<float>(_zoomScale, 0.f, 1.f);
	FPSCamera->FieldOfView = FMath::Lerp<float>(90.f, 45.f, _zoomScale);

	{
		FRotator rotation = Controller->GetControlRotation();
		rotation.Yaw += _camInput.X;
		rotation.Pitch += _camInput.Y;
		Controller->SetControlRotation(rotation);
	}
	
	if (!_moveInput.IsZero()) {
		_moveInput = _moveInput.GetSafeNormal() * MoveSpeed;
		FVector location = GetActorLocation();
		location += GetActorForwardVector() * _moveInput.X * DeltaTime;
		location += GetActorRightVector() * _moveInput.Y * DeltaTime;
		SetActorLocation(location);
	}
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind action maps
	InputComponent->BindAction("Zoom", IE_Pressed, this, &AFPSCharacter::CamZoomIn);
	InputComponent->BindAction("Zoom", IE_Released, this, &AFPSCharacter::CamZoomOut);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::JumpStart);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::JumpEnd);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AFPSCharacter::Fire);

	// Bind axis maps
	InputComponent->BindAxis("MoveX", this, &AFPSCharacter::MoveX);
	InputComponent->BindAxis("MoveY", this, &AFPSCharacter::MoveY);
	InputComponent->BindAxis("CamPitch", this, &AFPSCharacter::CamPitch);
	InputComponent->BindAxis("CamYaw", this, &AFPSCharacter::CamYaw);
}

void AFPSCharacter::MoveX(float axis) {
	_moveInput.X = FMath::Clamp<float>(axis, -1.f, 1.f);
}

void AFPSCharacter::MoveY(float axis) {
	_moveInput.Y = FMath::Clamp<float>(axis, -1.f, 1.f);
}

void AFPSCharacter::CamPitch(float axis) {

	_camInput.Y = axis;
}

void AFPSCharacter::CamYaw(float axis) {

	_camInput.X = axis;
}

void AFPSCharacter::CamZoomIn() {
	_isZooming = true;
}

void AFPSCharacter::CamZoomOut() {
	_isZooming = false;
}

void AFPSCharacter::JumpStart() {
	// Unreal's Character class implements this
	bPressedJump = true;
}

void AFPSCharacter::JumpEnd() {
	bPressedJump = false;
}

void AFPSCharacter::Fire() {
	if (ProjectileClass) {
		FVector CamLoc;
		FRotator CamRot;
		GetActorEyesViewPoint(CamLoc, CamRot);

		MuzzleOffset.Set(MuzzleOffset.X, MuzzleOffset.Y, MuzzleOffset.Z);

		FVector MuzzleLocation = CamLoc + FTransform(CamRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CamRot;
		MuzzleRotation.Pitch += ProjectilePitch;

		UWorld* World = GetWorld();

		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile) {
				FVector LanchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LanchDirection);
			}
		}
	}
}