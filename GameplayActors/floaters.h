// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floaters.generated.h"

UCLASS()
class FIRSTPROJECT_API Afloaters : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Afloaters();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyStaticMesh")
	UStaticMeshComponent* staticmesh;//initializing static mesh//

	// location of the actor set by SetActorLocation()//
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, category = "FloaterVariables")
	FVector initloc;

	//location of the actor when dragged in from content folder. it is used as a record for past location of actor//
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "FloaterVariables")
	FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FloaterVariables")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariables")
	FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariables")
	bool bFloatFromPlaced;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariables")
	bool bShouldFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FloaterVariables")
	bool bInitializeFloaterLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloaterVariables")
	FVector InitForce;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloaterVariables")
	FVector InitTorque;

private:
	float runningTime;
	float BaseZLocation;

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "FloaterVariables")
	float a; //Amplitude
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariables")
	float b; //Period = 2*pi/abs(b)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariables")
	float c;//Phase Shift = c/b
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariables")
	float d;//Vertical Shift

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
