// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "collider.generated.h"

UCLASS()
class FIRSTPROJECT_API Acollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Acollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere , Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UCollidorMovementComponent* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;//Syntax to Override any inherited function//
																		  //will be overriden in .cpp file//
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* mesh) { MeshComponent = mesh; }

	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent; }
	FORCEINLINE void SetSphereComponent(USphereComponent* mesh) { SphereComponent = mesh; }

	FORCEINLINE UCameraComponent* GetCameraComponent() { return Camera; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* Incamera) { Camera = Incamera; }

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* InSpring) { SpringArm = InSpring; }

private:
	void MoveForward(float input);
	void MoveRight(float input);
	void PitchCamera(float input);
	void YawCamera(float input);

	FVector2D CameraInput;
};
