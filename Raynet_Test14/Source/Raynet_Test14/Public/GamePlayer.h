// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GamePlayer.generated.h"

/*
Class holds details and movement of a player
*/

const bool TERMINALCARD_UNUSED = false;
const bool TERMINALCARD_USED = true;

UENUM ( BlueprintType )
enum class WinState: uint8 {
	Normal, Win, fail,
};

UENUM ( BlueprintType )
enum class ShowType:uint8 {
	BackB,
	LinkB,
	LinkY,
	VirusB,
	VirusY,
	FireWall,
	Null,
};

UENUM ( BlueprintType )
enum class TerminalCard: uint8 {
	LineBoost = 0, Firewall = 1, VirusCheck = 2, NotFound = 3
};

UENUM ( BlueprintType )
enum class ServerShowingOff: uint8 {
	Link,Virus,Null
};

USTRUCT ( BlueprintType )
struct FPawnType {
	GENERATED_BODY ()

	UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
		bool _IsShowingOff = false;
	UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
		bool _IsMovePoint = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool _IsLineBoosting = false;
//	UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
//		bool _IsSelected = false;
	UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
		TEnumAsByte<ShowType> _Type;
};


UCLASS()
class RAYNET_TEST14_API AGamePlayer : public AActor
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

	UPROPERTY ( BlueprintReadOnly )
		int32 _server_V = 0;
	UPROPERTY ( BlueprintReadOnly )
		int32 _server_L = 0;
	UPROPERTY ( BlueprintReadOnly )
		int32 _dataBase_V = 0;
	UPROPERTY ( BlueprintReadOnly )
		int32 _dataBase_L = 0;
	UPROPERTY ( BlueprintReadOnly )
		TArray<bool>_terminal;
	UPROPERTY ( BlueprintReadOnly )
		TEnumAsByte<ServerShowingOff> Showingoff = ServerShowingOff::Null;



	int32 _playerID;

	TWeakObjectPtr<AGamePlayer> _enemy;

	void setEnemy ( TWeakObjectPtr<AGamePlayer> EnemyPlayer );
	void setID ( int32 ID );

	TWeakObjectPtr<AGamePlayer> getEnemy ();

	UFUNCTION ( BlueprintCallable, Category = "default" )
		bool Win ();

		bool addToServer ( bool isShowingOff, bool islineboosting, ShowType Type );

		bool addToDataBase ( bool islineboosting,ShowType Type );

		bool getTerminalUse ( TerminalCard card );

		void setTerminalUse ( TerminalCard card, bool state );
};
