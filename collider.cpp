// Fill out your copyright notice in the Description page of Project Settings.


#include "collider.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CollidorMovementComponent.h"

// Sets default values
Acollider::Acollider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);//Sets Sphere COmponent as Root Component//
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));	

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAssest(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshComponentAssest.Succeeded())//succeded returns a boolean telling if FObjectFinder succeeded or not//
	{
		MeshComponent->SetStaticMesh(MeshComponentAssest.Object);
		MeshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);//The name of the socket at the end of the spring arm//
																		//looking back towards the spring arm origin//

	OurMovementComponent = CreateDefaultSubobject<UCollidorMovementComponent>(TEXT("OurMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;//Updated Component refers to component on which movement Component WIll Be Apllied//

	CameraInput = FVector2D(0.f, 0.f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void Acollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	//we change the rotation of springarm because if we change actor's pitch The ACtor will Roatate Up and down// 
	FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y, -80.f, -15.f);
	SpringArm->SetWorldRotation(NewSpringArmRotation);
}

// Called to bind functionality to input
void Acollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this,&Acollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this,&Acollider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &Acollider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &Acollider::YawCamera);
}

void Acollider::MoveForward(float input)
{
	FVector Forward = GetActorForwardVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Forward * input);
	}
}
void Acollider::MoveRight(float input)
{
	FVector Right = GetActorRightVector();
	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Right * input);
	}
}

void Acollider::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}
void Acollider::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

UPawnMovementComponent* Acollider::GetMovementComponent() const
{
	return OurMovementComponent;
}