// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "critter.generated.h"

UCLASS()
class FIRSTPROJECT_API Acritter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Acritter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	FVector CurrentVelocity;
	float MaxSpeed;

};
