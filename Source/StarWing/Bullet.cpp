// Fill out your copyright notice in the Description page of Project Settings.

#include "StarWing.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> BulletMesh;
		FConstructorStatics()
			: BulletMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	

	// Create static mesh component
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh0"));
	BulletMesh->SetStaticMesh(ConstructorStatics.BulletMesh.Get());
	RootComponent = BulletMesh;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	MovementComponent->SetUpdatedComponent(RootComponent);
	MovementComponent->ProjectileGravityScale = 0; //Don’t use gravity
	MovementComponent->InitialSpeed = 3000.f;
	MovementComponent->MaxSpeed = 3000.f;
	MovementComponent->bShouldBounce = false;

	InitialLifeSpan = 3.0f;
	

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

