// Nicholas Wile 2025 - Freely use this code for any purpose.

// Our custom class.
#include "LevitatingActor.h"

// Particle system class for adding a particle system component to our actor.
#include "Particles/ParticleSystemComponent.h"

// Constructor - custom implementation for Actor's initialization.
ALevitatingActor::ALevitatingActor()
{
	// This actor calls tick (updates) every frame.
	PrimaryActorTick.bCanEverTick = true;
	
	// Assign VisualMesh reference (defined in header file) a StaticMeshComponent.
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// Attach component to Actor
	VisualMesh->SetupAttachment(RootComponent);

	// Locate cube mesh from Unreal's Starter Content assets.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));

	// Set StaticMesh to the cube mesh, if it was located.
	if (CubeVisualAsset.Succeeded()) {
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// Setup a partcile system on the mesh to make it look cooler.
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	ParticleSystemComponent->SetupAttachment(VisualMesh);
	ParticleSystemComponent->bAutoActivate = true;
	ParticleSystemComponent->SetRelativeLocation(ParticleLocation);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire"));

	if (ParticleAsset.Succeeded()) {
		ParticleSystemComponent->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void ALevitatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame. Unreal Engine's Update() function. 
void ALevitatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get current location and rotation of actor.
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	
	// Scale actor height.
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * HoverSpeed; 
	
	// Rotate actor at 20degs per second.
	float DeltaRotation = DeltaTime * RotationSpeed; 
	NewRotation.Yaw += DeltaRotation;

	SetActorLocationAndRotation(NewLocation, NewRotation);
}

