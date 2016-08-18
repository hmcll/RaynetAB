// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GamePlayer.generated.h"

UENUM ( BlueprintType )
enum class PawnType: uint8 {
	Link, Virus, Null
};

UENUM ( BlueprintType )
enum class WinState: uint8 {
	Normal, Win, fail,
};

UENUM ( BlueprintType )
enum class TerminalCard: uint8 {
	LineBoost = 0, Firewall = 1, VirusCheck = 2, NotFound = 3
};

UCLASS()
class RAYNETAB_TEST13_API AGamePlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY ( BlueprintReadWrite, EditAnywhere )
		int32 _server_V;
	UPROPERTY ( BlueprintReadWrite, EditAnywhere )
		int32 _server_L;
	UPROPERTY ( BlueprintReadWrite, EditAnywhere )
		int32 _dataBase_V;
	UPROPERTY ( BlueprintReadWrite, EditAnywhere )
		int32 _dataBase_L;
	UPROPERTY ( BlueprintReadWrite, EditAnywhere )
		TArray<bool>_terminal;

	TWeakObjectPtr<AGamePlayer> _enemy;

	void setEnemy ( TWeakObjectPtr<AGamePlayer> EnemyPlayer );

	TWeakObjectPtr<AGamePlayer> getEnemy ();
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool Win ();
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool addToServer ( PawnType Type );
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool addToDataBase ( PawnType Type );
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool getTerminalUse ( TerminalCard card );
	UFUNCTION ( BlueprintCallable, Category = "default" )
		void setTerminalUse ( TerminalCard card, bool state );
	
};
