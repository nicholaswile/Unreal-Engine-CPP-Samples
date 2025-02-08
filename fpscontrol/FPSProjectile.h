// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "FPSProjectile.generated.h"

UCLASS()
class CPPSAMPLES_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	float ColliderRadius = 15.f;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float InitialSpeed = 3000.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 3000.f;

	UPROPERTY(EditAnywhere)
	float Bounciness = 0.3f;

	UPROPERTY(EditAnywhere)
	float GravityScale = 0.f;

	UPROPERTY(EditAnywhere)
	bool Bouncy = true;

	UPROPERTY(EditAnywhere)
	bool RotationFollowsVelocity = true;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UMaterialInstanceDynamic* ProjectileMaterial;

	UPROPERTY(EditAnywhere)
	FVector ProjectileScale = FVector(0.09f, 0.09f, 0.09f);

	UPROPERTY(EditAnywhere)
	float LifeSpan = 3.f;

	UPROPERTY(EditAnywhere)
	float ImpulseSpeed = 100.f;

	UFUNCTION()
	void FireInDirection(const FVector &FireDirection);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
