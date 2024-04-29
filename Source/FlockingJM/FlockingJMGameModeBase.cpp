// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlockingJMGameModeBase.h"

AFlockingJMGameModeBase::AFlockingJMGameModeBase() {
    AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;
}

void AFlockingJMGameModeBase::BeginPlay() {
    Manager = NewObject<UFlockManager>();
    Manager->Init(GetWorld(), AgentMesh);
}

void AFlockingJMGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    Manager->FlockUpdate();
};