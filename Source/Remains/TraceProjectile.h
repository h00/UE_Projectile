// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TraceProjectile.generated.h"

UCLASS()
class REMAINS_API ATraceProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATraceProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Velocity;
	float Gravity;
	float Mass; // TODO should we use this or pull from mesh component?
	float AirFriction; // not used currently. total place holder found at https://www.physicsforums.com/threads/mysterious-video-game-drag-model-any-ideas.686743


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float TotalTime; // used to calculate vertical velocity
};
