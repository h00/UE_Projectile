// Fill out your copyright notice in the Description page of Project Settings.

#include "Remains.h"
#include "TraceProjectile.h"

// Sets default values
ATraceProjectile::ATraceProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mass = 10.f;
	Gravity = 980.0f;
	//Velocity = 5000.f;
	//Velocity = 36576.f; // 9mm handgun
	//Velocity = 85344.f; // .762 rifle, I think
	Velocity = 9144.f; // arrow, 6858.f (recurve), 9144.f (compound)

	AirFriction = -0.0009324f;
	TotalTime = 0.f;
}

// Called when the game starts or when spawned
void ATraceProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(15.0f); // DEBUG decrease later
	UE_LOG(LogTemp, Warning, TEXT("PROJECTILE: Location: %s, Rotation: %s"), *GetActorLocation().ToString(), *GetActorRotation().ToString());

}

// Called every frame
void ATraceProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	Since we're using GetActorForwardVector(), we are not calculating horizontal and
	vertical velocity seperately. These calculations may be an approximation of the
	projectile motion formula, but they feel close enough to me for now.
	*/

	// track total time spent in ticks. used to determine vertical velocity (proctile drop)
	TotalTime += DeltaTime;

	FVector Start = this->GetActorLocation();
	FVector End = Start + GetActorForwardVector() * Velocity * DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("Start: %s, End: %s"), *Start.ToString(), *End.ToString());

	/*
	Update projectile's vertical velocity (drop).
	the GetActorForwardVector() * Velocity * DeltaTime is providing
	vertical velocity of it's own
	*/
	float VelocityV = (Gravity * TotalTime * TotalTime) * .5;
	End.Z -= VelocityV * DeltaTime;

	// define linetrace collision params
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this); // ignore self actor, just in case

							   // run linetrace
	FHitResult RaycastHit;
	GetWorld()->LineTraceSingleByChannel(RaycastHit, Start, End, ECollisionChannel::ECC_WorldDynamic, CQP);

	// handle collision, else update projectile location/rotation/speed
	AActor* TargetActor = RaycastHit.GetActor();
	if (TargetActor)
	{
		DrawDebugBox(GetWorld(), RaycastHit.ImpactPoint, FVector(5.f), FColor::Red, false, 3.5f, 0.f, 4.f);

		FString TargetName = RaycastHit.GetActor()->GetFName().ToString();
		UE_LOG(LogTemp, Warning, TEXT("Target hit: %s, Location: %s"), *TargetName, *RaycastHit.ImpactPoint.ToString());

		// TODO handle destruction of projectile
		Destroy();
		// check if material is penetrable
		// if so, reduce velocity
		// else 
		// destroy projectile
		// spawn particle affect
	}
	else {
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.25f, 0, 6);
		SetActorLocation(End);
	}

}

