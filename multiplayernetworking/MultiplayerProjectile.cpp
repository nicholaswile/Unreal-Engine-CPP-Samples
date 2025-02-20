// Nicholas Wile 2025 - Freely use this code for any purpose.


#include "MultiplayerProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMultiplayerProjectile::AMultiplayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	// Create root collider
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereCollider->InitSphereRadius(_SphereRadius);
	SphereCollider->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereCollider;

	// Attach mesh (graphics)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	
	if (DefaultMesh.Succeeded()) {
		VisualMesh->SetStaticMesh(DefaultMesh.Object);
		VisualMesh->SetRelativeLocation(_DefaultLocation);
		VisualMesh->SetRelativeScale3D(_DefaultScale);
	}

	// Attach particle fx for projectile explosion
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosion(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (DefaultExplosion.Succeeded()) {
		ExplosionFX = DefaultExplosion.Object;
	}

	// Projectile behavior that will be replicated across clients on the server
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(SphereCollider);
	ProjectileMovement->InitialSpeed = _InitialSpeed;
	ProjectileMovement->MaxSpeed = _MaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = _GravityScale;

	DamageType = UDamageType::StaticClass();
	Damage = _Damage;

	// Call function ProjectileImpact when projectile hits an object on server only
	if (GetLocalRole() == ROLE_Authority) {
		SphereCollider->OnComponentHit.AddDynamic(this, &AMultiplayerProjectile::OnProjectileImpact);
	}
}

// Called when the game starts or when spawned
void AMultiplayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMultiplayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMultiplayerProjectile::Destroyed() {
	FVector SpawnLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionFX, SpawnLocation, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);

}

// Any collision destroys this projectile, but if it collides with another actor, apply damage to the actor
void AMultiplayerProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult) {
	if (OtherActor) {
		UGameplayStatics::ApplyPointDamage(OtherActor, Damage, NormalImpulse, HitResult, GetInstigator()->Controller, this, DamageType);
	}
	Destroy();
}

