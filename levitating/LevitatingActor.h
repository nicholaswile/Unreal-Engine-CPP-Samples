// Nicholas Wile 2025 - Freely use this code for any purpose.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevitatingActor.generated.h"

UCLASS()
class CPPSAMPLES_API ALevitatingActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALevitatingActor();

	// Reference to the graphics for the levitating object.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisualMesh = nullptr;

	UPROPERTY(EditAnywhere)
	float HoverSpeed = 20.f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 20.f;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystemComponent = nullptr;

	UPROPERTY(EditAnywhere)
	FVector ParticleLocation = FVector(0.0f, 0.0f, 0.0f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
