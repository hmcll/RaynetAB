// Copyright(C) 2015 - 2016  Raynet AB Development Team

#pragma once

#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "Enums_and_Structs.h"
#include "ChessBoard.h"
#include "RaynetAB_Test13GameState.generated.h"


UCLASS()
class RAYNETAB_TEST13_API ARaynetAB_Test13GameState: public AGameStateBase {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Variable")
		TArray<FPawnType> Refresh;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Variable")
		FChessboardPlayer RefreshPlayer;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Variable")
		FChessboardPlayer RefreshPlayer_Enemy;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Variable")
		bool RefreshState = false;
	
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Variable")
		RoundRefreshState roundRefresh = RoundRefreshState::None;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Variable")
		bool Flag_HostWon = false;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Variable")
		bool Flag_HostGoingFirst = false;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Variable")
		bool MovePointToServer = false;
	
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Variable")
		TArray<FMove_C> MoveStack;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Variable")
		EGameState _GameState;
};
