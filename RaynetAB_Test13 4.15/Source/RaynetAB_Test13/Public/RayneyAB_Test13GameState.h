// Copyright(C) 2015 - 2016  Raynet AB Development Team

#pragma once

#include "GameFramework/GameStateBase.h"
#include "GamePlayer.h"
#include "Net/UnrealNetwork.h"
#include "RayneyAB_Test13GameState.generated.h"

/**
 * 
 */

USTRUCT ( BlueprintType )
struct FMove_C {
	GENERATED_BODY ()

	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool IsTerminal = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool AdditionalInfo = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		FVector2D MoveFrom;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		FVector2D MoveTo;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		TerminalCard Type;
};

UENUM(BlueprintType)
enum class EGameState : uint8 {
	Waiting,
	Starting,
	Setting_BothNotFinished,
	Setting_OneSideNotFinished,
	Setting_BothFinished,
	Playing,
	Ending
};

UCLASS()
class RAYNETAB_TEST13_API ARayneyAB_Test13GameState : public AGameStateBase
{
	GENERATED_BODY ()
public:
	UPROPERTY (Replicated)
		bool Flag_OnesideFinished = false;

	UPROPERTY ( BlueprintReadWrite, Replicated, Category = "Variable" )
		EGameState state = EGameState::Waiting;

	ARayneyAB_Test13GameState ();

	UFUNCTION ( Server, Reliable, WithValidation , Category = "Function" )
		void Server_SetPawn_Arrangement (bool Offensive,const TArray<ShowType>& Setting);
	
	UFUNCTION ( Server, Reliable, WithValidation ,Category = "Function" )
		void Server_Confirm ();

	UFUNCTION ( Server, Reliable, WithValidation , Category = "Function" )
		void Server_Move ( FMove_C move);
	
	UFUNCTION ( Server, Reliable, WithValidation , Category = "Function" )
		void Server_Win ( bool EnemyWinState );
};
