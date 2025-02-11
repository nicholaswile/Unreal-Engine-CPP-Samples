// Nicholas Wile 2025 - Freely use this code for any purpose.


#include "ThirdPersonCharacter.h"

// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	GetMesh()->SetRelativeLocationAndRotation(StartLocation, FQuat(StartRotation));

	SpringArm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	// Enable CanCrouch in the BP_ThirdPersonCharacter Blueprint editor on the CharacterMovement component.
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Controlling Third Person Character"));

	SetActorLocation(SpawnLocation);

	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;

}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &AThirdPersonCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &AThirdPersonCharacter::MoveY);
	PlayerInputComponent->BindAxis("CamYaw", this, &AThirdPersonCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CamPitch", this, &AThirdPersonCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AThirdPersonCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AThirdPersonCharacter::EndJump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AThirdPersonCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AThirdPersonCharacter::EndCrouch);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AThirdPersonCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AThirdPersonCharacter::EndSprint);

}

void AThirdPersonCharacter::MoveX(float axis) {
	if (Controller != nullptr && axis != 0) {
		// Get direction that character is facing (yaw)
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// Get the x direction relative to the direction they're facing and move in that direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, axis);
	}
}

void AThirdPersonCharacter::MoveY(float axis) {
	if ((Controller != nullptr && axis != 0)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// Get the y direction relative to the direction they're facing and move in that direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, axis);
	}
}

// These are implemented in the Character class that this class inherits from
void AThirdPersonCharacter::StartCrouch() {
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Start Crouch"));
	const wchar_t* c = CanCrouch() ? L"True" : L"False";
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, c);
	Crouch();
}

void AThirdPersonCharacter::EndCrouch() {
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("End Crouch"));
	UnCrouch();
}

void AThirdPersonCharacter::StartSprint() {
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Start Sprint"));
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void AThirdPersonCharacter::EndSprint() {
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, TEXT("End Sprint"));
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

void AThirdPersonCharacter::StartJump() {
	Jump();
}

void AThirdPersonCharacter::EndJump() {
	StopJumping();
}