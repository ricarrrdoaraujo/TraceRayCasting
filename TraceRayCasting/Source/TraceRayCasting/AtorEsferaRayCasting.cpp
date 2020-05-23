// Fill out your copyright notice in the Description page of Project Settings.


#include "AtorEsferaRayCasting.h"
#include "Components/BillboardComponent.h"
#include "DrawDebugHelpers.h"
#include "WorldCollision.h"
#include "Engine/World.h"

// Sets default values
AAtorEsferaRayCasting::AAtorEsferaRayCasting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Cria um componente apenas para dar uma possibilidade visual quando usarmos o editor
	UBillboardComponent* BillBoard = CreateDefaultSubobject<UBillboardComponent>(FName("BillBoard"));
	RootComponent = BillBoard;

}

// Called when the game starts or when spawned
void AAtorEsferaRayCasting::BeginPlay()
{
	Super::BeginPlay();
	
	//Criado um array capaz de armazenar Structs do tipo FHitResult
	//Armazena uma séria de informacoes da colisao
	TArray<FHitResult> ResultadosColisao;

	//Obtemos a localizacao deste ator
	FVector LocalizacaoDoAtor = GetActorLocation();
	//Indicamos que queremos que o final da esfera de raycasting seja 
	//Localizacao do ator + 100 em x, y e z (soma de vetores)
	FVector FinalDaEsferaDebug = LocalizacaoDoAtor + FVector(100.f, 100.f, 100.f);

	//Criamos um componente de colisao e setamos que ele será uma esfera, através da funcao make sphere (poderia ser um box, capsule)
	//Raio será 200
	FCollisionShape ColisaoEsferica = FCollisionShape::MakeSphere(200.f);

	//Desenhamos uma esfera para analisarmos como será fisicamente a esfera que será criada em SweepMultiByChannel. Ou seja, quem detecta a colisao é SweepMultiByChannel
	//DrawDebugSphere é apenas para o programador conseguir enxergar o ray casting em ação
	DrawDebugSphere(GetWorld(), LocalizacaoDoAtor, ColisaoEsferica.GetSphereRadius(), 200, FColor::Red, true, -1.f, (uint8)8, 0.5f);

	//aqui chamamos a funcao e enviamos seus parametros
	bool OcorreuColisao = GetWorld()->SweepMultiByChannel(ResultadosColisao, LocalizacaoDoAtor, FinalDaEsferaDebug, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, ColisaoEsferica);
	//No nosso caso indica que o trace channer é o WorldStatic e determina que tipo de Canal de Colisao a esfera deve analisar

	if (OcorreuColisao)
	{
		//Lembrando auto é utilizado para que em tempo de compilacao o tipo de colisoes seja estabelecido automaticamente, 
		// a depender do tipo de ResultadosColisao

		//Já que o ResultadosColisao é um array, o for vai varrer este array e a cada
		//passada vai colocando o elemento na variavel auto& Colisoes
		//Entao logo coloca na tela o nome do ator
		for (auto& Colisoes : ResultadosColisao)
		{
			UE_LOG(LogTemp, Error, TEXT("Nome d Ator: %s"), *Colisoes.Actor->GetName());
		}
	}
}

// Called every frame
void AAtorEsferaRayCasting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

