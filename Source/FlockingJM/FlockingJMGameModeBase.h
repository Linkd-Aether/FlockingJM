// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockManager.h"
#include "FlockingJMGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLOCKINGJM_API AFlockingJMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		AFlockingJMGameModeBase();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* AgentMesh;

	UPROPERTY()
		UFlockManager* Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
