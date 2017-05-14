// Copyright(C) 2015 - 2016  Raynet AB Development Team

#pragma once

#include "GameFramework/GameStateBase.h"
#include "GamePlayer.h"
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


UCLASS()
class RAYNETAB_TEST13_API ARayneyAB_Test13GameState : public AGameStateBase
{
	GENERATED_BODY()
	
	
	
	
};
