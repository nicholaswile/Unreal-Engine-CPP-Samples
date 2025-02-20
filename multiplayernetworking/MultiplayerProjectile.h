// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultiplayerProjectile.generated.h"

UCLASS()
class MULTIPLAYER_API AMultiplayerProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiplayerProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "FX")
	class UParticleSystem* ExplosionFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float Damage;

	virtual void Destroyed() override;
	UFUNCTION(Category="Projectile")
	void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


private:
	UPROPERTY(EditAnywhere)
	float _SphereRadius = 37.5f;
	
	UPROPERTY(EditAnywhere)
	FVector _DefaultLocation = FVector(0.f, 0.f, -37.5);

	UPROPERTY(EditAnywhere)
	FVector _DefaultScale = FVector(0.75f, 0.75f, -0.75f);

	UPROPERTY(EditAnywhere)
	float _InitialSpeed = 1500.f;

	UPROPERTY(EditAnywhere)
	float _MaxSpeed = 1500.f;

	UPROPERTY(EditAnywhere)
	float _GravityScale = 0.f;

	UPROPERTY(EditAnywhere)
	float _Damage = 10.f;
};