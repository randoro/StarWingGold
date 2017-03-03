// Fill out your copyright notice in the Description page of Project Settings.

#include "StarWing.h"
#include "StarWingPawn.h"
#include "Ring.h"
#include "StarWingGameMode.h"


// Sets default values
ARing::ARing()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> RingMesh;
		FConstructorStatics()
			: RingMesh(TEXT("/Game/ring.ring"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	RingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RingMesh0"));
	RingMesh->SetStaticMesh(ConstructorStatics.RingMesh.Get());
	RootComponent = RingMesh;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh0"));
	Trigger->AttachTo(RootComponent);
	Trigger->SetBoxExtent(FVector(70.f, 70.f, 18.f)); //fix size
	


	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARing::OnBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ARing::OnEndOverlap);


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARing::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARing::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(AStarWingPawn::StaticClass()))
	{
		RingMesh->SetVisibility(false);
		AStarWingGameMode* gm = (AStarWingGameMode*)GetWorld()->GetAuthGameMode();
		int32 time = gm->GetTime();
		gm->SetTime(time+3000);
		this->Destroy();
	}
	//(AStarWingGameMode*)GetWorld()->GetAuthGameMode();
}


void ARing::OnEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	RingMesh->SetVisibility(true);
}