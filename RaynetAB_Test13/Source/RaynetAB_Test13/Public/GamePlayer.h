// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GamePlayer.generated.h"

/*
Class holds details and movement of a player
*/

UENUM ( BlueprintType )
enum class WinState: uint8 {
	Normal, Win, fail,
};

UENUM ( BlueprintType )
enum class ShowType:uint8 {
	BackB,
	BackBL,
	LinkB,
	LinkBL,
	LinkY,
	LinkYL,
	VirusB,
	VirusBL,
	VirusY,
	VirusYL,
	FireWall,
	Null,
};

UENUM ( BlueprintType )
enum class TerminalCard: uint8 {
	LineBoost = 0, Firewall = 1, VirusCheck = 2, NotFound = 3
};

USTRUCT ( BlueprintType )
struct FPawnType {
	GENERATED_BODY ()

		UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
		bool _IsShowingOff = false;
	UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
		bool _IsMovePoint = false;
	UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
		bool _IsSelected = false;
	UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
		TEnumAsByte<ShowType> _Type;
};


UCLASS()
class RAYNETAB_TEST13_API AGamePlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	AGamePlayer ();
	// Sets default values for this actor's properties
	AGamePlayer(int32 playerID);

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

	int32 _playerID;

	TWeakObjectPtr<AGamePlayer> _enemy;

	void setEnemy ( TWeakObjectPtr<AGamePlayer> EnemyPlayer );
	void setID ( int32 ID );

	TWeakObjectPtr<AGamePlayer> getEnemy ();
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool Win ();
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool addToServer ( ShowType Type );
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool addToDataBase ( ShowType Type );
	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool getTerminalUse ( TerminalCard card );
	UFUNCTION ( BlueprintCallable, Category = "default" )
		void setTerminalUse ( TerminalCard card, bool state );
};
