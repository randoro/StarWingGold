// Fill out your copyright notice in the Description page of Project Settings.

#include "StarWing.h"
#include "CubeBox.h"
#include "StarWingPawn.h"
#include "StarWingGameMode.h"
#include "Bullet.h"


// Sets default values
ACubeBox::ACubeBox()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> BoxMesh;
		FConstructorStatics()
			: BoxMesh(TEXT("/Game/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh0"));
	BoxMesh->SetStaticMesh(ConstructorStatics.BoxMesh.Get());
	RootComponent = BoxMesh;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh0"));
	Trigger->SetBoxExtent(FVector(50, 50, 50), true);
	Trigger->AttachTo(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACubeBox::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ACubeBox::OnEndOverlap);

	this->SetActorScale3D(FVector(10, 10, 5));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeBox::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACubeBox::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AStarWingPawn::StaticClass()))
	{
		//BoxMesh->SetVisibility(false);
		AStarWingGameMode* gm = (AStarWingGameMode*)GetWorld()->GetAuthGameMode();
		float health = gm->GetHealth();
		gm->SetHealth(health - 0.20f);
		this->Destroy();
	}
	else if (OtherActor->IsA(ABullet::StaticClass()))
	{
		int32 randomValue = FMath::RandRange(0, 100);
		if (randomValue < 30) {
			this->Destroy();
		}
		OtherActor->Destroy();
	}
	//(AStarWingGameMode*)GetWorld()->GetAuthGameMode();
}


void ACubeBox::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//BoxMesh->SetVisibility(true);
}
