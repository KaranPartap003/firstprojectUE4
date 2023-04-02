// Fill out your copyright notice in the Description page of Project Settings.


#include "critter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
Acritter::Acritter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//inherited from actor.h//
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent()); //Attaches to root component in BP//
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));//No 2 CDS calls can have same TEXT//
	camera->SetupAttachment(GetRootComponent());
	camera->SetRelativeLocation(FVector(-300.f, 0.0f, 300.0f));
	camera->SetRelativeRotation(FRotator(-45.f, 0.0f, 0.0f));
	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;

	//AutoPossessPlayer = EAutoReceiveInput::Player0;//posses the default Pawn//

}

// Called when the game starts or when spawned
void Acritter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void Acritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &Acritter::MoveForward);//Binds the axis mappings to the given function//
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &Acritter::MoveRight);
}

void Acritter::MoveForward(float value)//this func. will change velocity and velocity will change the position using Tick Function//
{
	CurrentVelocity.X = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}
void Acritter::MoveRight(float value)
{
	CurrentVelocity.Y = FMath::Clamp(value, -1.f, 1.f) * MaxSpeed;
}

