// Fill out your copyright notice in the Description page of Project Settings.


#include "RayCastPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

void ARayCastPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	//Amarrando o Atirar definido no editor (Input) ao AtirarRayCast
	InputComponent->BindAction("Atirar", EInputEvent::IE_Released, this, &ARayCastPlayerController::AtirarRayCast);
}

void ARayCastPlayerController::AtirarRayCast()
{
	//Distancia máxima a ser percorrida pelo raio(trace)
	float Tamanho = 1000.f;

	//Neste caso foi estabelecido que a origem do raio será a câmera
	//Logo achamos o vetor frente da câmera(ou seja para onde a câmera está apontando "encarando")
	FVector Direcao = PlayerCameraManager->GetActorForwardVector();

	//Ponto de origem de onde vai ser disparado o raio(Raycast)
	FVector Origem = LocalizacaoPontoDeVisaoDoPlayer;

	//Será o vetor de Origem somado com o vetor Direcao multiplicado por 1000, que é o
	//tamanho
	FVector PontoFinal = LocalizacaoPontoDeVisaoDoPlayer + (RotacaoPontoDeVisaoDoPlayer.Vector() * Tamanho);

	//Variavel Struct que vai receber todos os detalhes de colisao do raio
	//Caso ocorra alguma colisao deste raio com algo
	FHitResult ResultadoDoHit;

	FCollisionQueryParams CollisionParams;

	bool ColidiuComAlgo = GetWorld()->LineTraceSingleByChannel(ResultadoDoHit, Origem, PontoFinal, ECollisionChannel::ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), Origem, PontoFinal, FColor::Red, false, 10.f, (uint8)0, 5.f);

	if (ColidiuComAlgo)
	{
		UE_LOG(LogTemp, Error, TEXT("Ator %s"), *ResultadoDoHit.Actor->GetName());
		UE_LOG(LogTemp, Error, TEXT("Ator %s"), *ResultadoDoHit.Location.ToString());
	}

}

void ARayCastPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// GetPlayerViewPoint - para onde o player está olhando
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(LocalizacaoPontoDeVisaoDoPlayer, RotacaoPontoDeVisaoDoPlayer);
}
