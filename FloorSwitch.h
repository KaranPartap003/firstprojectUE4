// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class FIRSTPROJECT_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	/* Overlap Volume for the functionality to be triggered */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
	class UBoxComponent* TriggerBox;
	
	/* Switch for the character to step on */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
	class UStaticMeshComponent* FloorSwitch;

	/* Door to open when the switch is stepped on */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
	UStaticMeshComponent* Door;

	/* Initioal location of the door*/
	UPROPERTY(BlueprintReadWrite , Category = "FloorSwitch" )
	FVector InitialDoorLocation;
	/* Initial location of switch */
	UPROPERTY(BlueprintReadWrite, Category = "FloorSwitch")
	FVector InitialSwitchLocation;

	FTimerHandle SwitchHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloorSwitch")
	float SwitchTime;
	void CloseDoor();

	bool bCharacterOnSwitch;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()// if a function is being delegated it must be a UFUNCTION //
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
	void RaiseDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
	void LowerDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
	void RaiseSwitch();
	UFUNCTION(BlueprintImplementableEvent, Category = "FloorSwitch")
	void LowerSwitch();
	UFUNCTION(BlueprintCallable, Category = "FloorSwitch")
	void UpdateDoorLocation(float Z); 
	UFUNCTION(BlueprintCallable, Category = "FloorSwitch")
	void UpdateSwitchLocation(float Z);
};
