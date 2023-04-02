// Fill out your copyright notice in the Description page of Project Settings.


#include "floaters.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
Afloaters::Afloaters()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	initloc = FVector(0.0f, 0.0f, 0.0f);
	PlacedLocation = FVector(0.0f);
	bInitializeFloaterLocation = false;
	bShouldFloat = false;
	InitialDirection = FVector(0.0f);
	InitForce = FVector(999999.0f, 0.0f, 0.0f);
	InitTorque = FVector(999999.0f, 0.0f, 0.0f);
	runningTime = 0.f;
	a = 1.f;
	b = 0.f;
	c = 0.f;
	d = 0.f;

	staticmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomMesh"));//CreateDefaultSubobject is used to create objects of a specific type specified inside < >//

}

// Called when the game starts or when spawned
void Afloaters::BeginPlay()
{
	Super::BeginPlay();

	PlacedLocation = GetActorLocation();

	if (bFloatFromPlaced) {
		initloc = PlacedLocation;
	}

	if (bInitializeFloaterLocation) {
		SetActorLocation(initloc);
	}

	BaseZLocation = PlacedLocation.Z;

	//staticmesh->AddForce(InitForce);
	//staticmesh->AddTorque(InitTorque);
	
}

// Called every frame
void Afloaters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat) {

		FVector NewLocation = GetActorLocation();
		NewLocation.Z = BaseZLocation + (a)*FMath::Sin((b)*runningTime - c) + d;
		SetActorLocation(NewLocation); 
		runningTime += DeltaTime;

		//FHitResult HitResult;
		//AddActorLocalOffset(InitialDirection, true, &HitResult);
		//FVector HitLocation = HitResult.Location;
		// to show live hit location:
		//UE_LOG(LogTemp, Warning, TEXT("hit location X: %f , Y:%f , Z: %f"), HitLocation.X, HitLocation.Y, HitLocation.Z);
	}

}

