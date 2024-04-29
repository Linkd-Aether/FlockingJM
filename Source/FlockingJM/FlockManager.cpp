#include "FlockManager.h"

#define NUM_AGENTS 20
#define SPAWN_RADIUS 1000.0f
#define MIN_FRAMES_BETWEEN_SPAWNS 600

void UFlockManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
	World = world;
	Mesh = mesh;

	// Create agents
	if (World != nullptr) {
		for (int i = 0; i < NUM_AGENTS; i++) {
			UE_LOG(LogTemp, Warning, TEXT("Creating agent %d"), i);
			SpawnAgent(Mesh, i);
		}
	}

}

void UFlockManager::FlockUpdate() {
	// Spawn new agent
	framesSinceLastSpawn++;
	if (framesSinceLastSpawn + (rand() % MIN_FRAMES_BETWEEN_SPAWNS) > MIN_FRAMES_BETWEEN_SPAWNS) {
		SpawnAgent(Mesh, Agents.Num());
	}

	for (int i = 0; i < Agents.Num(); i++) {
		Agents[i]->Velocity += R1(Agents[i]);
		Agents[i]->Velocity += R2(Agents[i]);
		Agents[i]->Velocity += R3(Agents[i]);
		R4(Agents[i]);
	}
}

void UFlockManager::SpawnAgent(UStaticMeshComponent* mesh, int id) {
	// Randomize spawn location
	FVector spawnLocation = FVector(FMath::RandRange(-SPAWN_RADIUS, SPAWN_RADIUS), FMath::RandRange(-SPAWN_RADIUS, SPAWN_RADIUS), FMath::RandRange(0.f, SPAWN_RADIUS * 2));
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	AAgent* agent = World->SpawnActor<AAgent>(spawnLocation, spawnRotation);
	agent->Init(mesh, id);
	Agents.Add(agent);
}

FVector UFlockManager::R1(AAgent* b) {
	FVector pcj = FVector(0.f);
	for (int i = 0; i < Agents.Num(); i++) {
		if (Agents[i] != b) {
			pcj += Agents[i]->GetActorLocation();
		}
	}
	pcj /= Agents.Num() - 1;
	return (pcj - b->GetActorLocation()) / 100.f;
}

FVector UFlockManager::R2(AAgent* b) {
	FVector c = FVector(0.f);
	for (int i = 0; i < Agents.Num(); i++) {
		if (Agents[i] != b) {
			if (FVector::Dist(b->GetActorLocation(), Agents[i]->GetActorLocation()) < 100.f) {
				c -= Agents[i]->GetActorLocation() - b->GetActorLocation();
			}
		}
	}
	return c;
}

FVector UFlockManager::R3(AAgent* b) {
	FVector pvj = FVector(0.f);
	for (int i = 0; i < Agents.Num(); i++) {
		if (Agents[i] != b) {
			pvj += Agents[i]->Velocity;
		}
	}
	pvj /= Agents.Num() - 1;
	return (pvj - b->Velocity) / 8.f;
}

void UFlockManager::R4(AAgent* b) {
	// Delete agent if it has lived for too long
	if (b->framesAlive + (rand() % MIN_FRAMES_BETWEEN_SPAWNS) > MIN_FRAMES_BETWEEN_SPAWNS) {
		Agents.Remove(b);
		b->Destroy();
	}
	else {
		b->framesAlive++;
	}
}