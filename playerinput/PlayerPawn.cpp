// Nicholas Wile 2025 - Freely use this code for any purpose.

// Custom class
#include "PlayerPawn.h"

// Unreal classes
#include "Camera/CameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn responds to player 1's input automatically when the game starts
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create empty root component for attaching other components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera 
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	// Create a scene component (it's empty, but we create a visual mesh)
	SceneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SceneComponent"));

	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(Location);
	Camera->SetRelativeRotation(Rotation);
	SceneComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		float Scale = SceneComponent->GetComponentScale().X;
		if (_bGrowing)
			Scale += DeltaTime;
		else
			Scale -= (DeltaTime * 0.5f);
		Scale = FMath::Clamp(Scale, 1.f, 2.f);
		SceneComponent->SetWorldScale3D(FVector(Scale));
	}

	{
		if (!_velocity.IsZero()) {
			FVector Move = GetActorLocation() + (_velocity * DeltaTime);
			SetActorLocation(Move);
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Bind input functions to input mappings

	// Respond to action mapping: grow key 
	InputComponent->BindAction("Grow", IE_Pressed, this, &APlayerPawn::StartGrow);
	InputComponent->BindAction("Grow", IE_Released, this, &APlayerPawn::StopGrow);

	// Respond to axis mapping: move x and y dirs
	InputComponent->BindAxis("MoveX", this, &APlayerPawn::MoveXaxis);
	InputComponent->BindAxis("MoveY", this, &APlayerPawn::MoveYaxis);
}

void APlayerPawn::MoveXaxis(float f) {
	_velocity.X = FMath::Clamp(f, -1.f, 1.f) * Speed;
}

void APlayerPawn::MoveYaxis(float f) {
	_velocity.Y = FMath::Clamp(f, -1.f, 1.f) * Speed;
}

void APlayerPawn::StartGrow() {
	_bGrowing = true;
}

void APlayerPawn::StopGrow() {
	_bGrowing = false;
}