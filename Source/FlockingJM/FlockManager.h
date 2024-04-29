#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "Engine/GameEngine.h"
#include "FlockManager.generated.h"

UCLASS()
class FLOCKINGJM_API UFlockManager : public UObject
{

public:
	GENERATED_BODY()

	// Sets default values for this empty's properties
	void Init(UWorld* world, UStaticMeshComponent* mesh);

	// Flocking rules
	FVector R1(AAgent* b);
	FVector R2(AAgent* b);
	FVector R3(AAgent* b);
	void R4(AAgent* b);

	// Called every frame
	void FlockUpdate();

private:
	void SpawnAgent(UStaticMeshComponent* mesh, int id);

	UWorld* World;
	UStaticMeshComponent* Mesh;
	TArray<class AAgent*> Agents;

	int framesSinceLastSpawn = 0;
};
