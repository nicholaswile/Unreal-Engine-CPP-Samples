// Nicholas Wile 2025 - Freely use this code for any purpose.

// Custom
#include "ThirdPersonPlayer.h"

// Engine
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AThirdPersonPlayer::AThirdPersonPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mesh->SetupAttachment(RootComponent);
	springarm->SetupAttachment(mesh);
	camera->SetupAttachment(springarm, USpringArmComponent::SocketName);

	springarm->SetRelativeLocationAndRotation(location, rotation);
	springarm->TargetArmLength = armLength[0];
	springarm->bEnableCameraLag = true;
	springarm->CameraLagSpeed = lagSpeed;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AThirdPersonPlayer::BeginPlay()
{
	Super::BeginPlay();

	InputComponent->BindAction("Zoom", IE_Pressed, this, &AThirdPersonPlayer::ZoomIn);
	InputComponent->BindAction("Zoom", IE_Released, this, &AThirdPersonPlayer::ZoomOut);

	InputComponent->BindAxis("MoveX", this, &AThirdPersonPlayer::MoveX);
	InputComponent->BindAxis("MoveY", this, &AThirdPersonPlayer::MoveY);
	InputComponent->BindAxis("CamPitch", this, &AThirdPersonPlayer::CamPitch);
	InputComponent->BindAxis("CamYaw", this, &AThirdPersonPlayer::CamYaw);
	
}

// Called every frame
void AThirdPersonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isZooming) {
		_fovFactor += DeltaTime / zoomSpeed[0];
	}
	else {
		_fovFactor -= DeltaTime / zoomSpeed[1];
	}
	_fovFactor = FMath::Clamp<float>(_fovFactor, 0.f, 1.f);

	camera->FieldOfView = FMath::Lerp<float>(fovRange[0], fovRange[1], _fovFactor);
	springarm->TargetArmLength = FMath::Lerp<float>(armLength[0], armLength[1], _fovFactor);

	{
		FRotator newRotation = GetActorRotation();
		newRotation.Yaw += _lookInput.X;
		SetActorRotation(newRotation);
	}

	{
		FRotator newRotation = springarm->GetComponentRotation();
		newRotation.Pitch += _lookInput.Y;
		springarm->SetWorldRotation(newRotation);
	}

	{
		if (!_moveInput.IsZero()) {
			_moveInput = _moveInput.GetSafeNormal() * 100.f;
			FVector newLocation = GetActorLocation();
			newLocation += GetActorForwardVector() * _moveInput.X * DeltaTime;
			newLocation += GetActorRightVector() * _moveInput.Y * DeltaTime;
			SetActorLocation(newLocation);
		}
	}
}

// Called to bind functionality to input
void AThirdPersonPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AThirdPersonPlayer::MoveX(float axis) {
	_moveInput.X = FMath::Clamp<float>(axis, -1.f, 1.f);
}

void AThirdPersonPlayer::MoveY(float axis) {
	_moveInput.Y = FMath::Clamp<float>(axis, -1.f, 1.f);
}

void AThirdPersonPlayer::CamPitch(float axis) {
	_lookInput.Y = axis;
}

void AThirdPersonPlayer::CamYaw(float axis) {
	_lookInput.X = axis;
}

void AThirdPersonPlayer::ZoomIn() {
	isZooming = true;
}

void AThirdPersonPlayer::ZoomOut() {
	isZooming = false;
}