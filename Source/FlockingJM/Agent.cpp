#include "Agent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAgent::AAgent()
{
	// Set this empty to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	Velocity = FVector();
}

void AAgent::Init(UStaticMeshComponent* mesh, int id)
{
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector loc = GetActorLocation();
	SetActorLocation(loc + Velocity);

	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(FVector(0.f), Velocity);
	SetActorRotation(rotation + FRotator(-90.f, 0.f, 0.f));
}
