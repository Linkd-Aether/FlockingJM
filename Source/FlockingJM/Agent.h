#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Agent.generated.h"

UCLASS()
class FLOCKINGJM_API AAgent : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this empty's properties
	AAgent();
	void Init(UStaticMeshComponent* mesh, int id);
	UStaticMeshComponent* Mesh;
	FVector Velocity;
	int framesAlive = 0;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
