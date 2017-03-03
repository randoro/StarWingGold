// Fill out your copyright notice in the Description page of Project Settings.

#include "StarWing.h"
#include "Goal.h"
#include "StarWingPawn.h"
#include "StarWingGameMode.h"


// Sets default values
AGoal::AGoal()
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
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh1"));
	BoxMesh->SetStaticMesh(ConstructorStatics.BoxMesh.Get());
	RootComponent = BoxMesh;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh1"));
	Trigger->SetBoxExtent(FVector(50, 50, 50), true);
	Trigger->AttachTo(RootComponent);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AGoal::OnEndOverlap);

	this->SetActorScale3D(FVector(10, 10, 5));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AGoal::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AStarWingPawn::StaticClass()))
	{
		//BoxMesh->SetVisibility(false);
		UGameplayStatics::OpenLevel(GetWorld(), "GameOverWin");
	}
	//(AStarWingGameMode*)GetWorld()->GetAuthGameMode();
}


void AGoal::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//BoxMesh->SetVisibility(true);
}

