// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ChessBoard.h"
#include "GameMain.generated.h"

/**
 * 
 */
UCLASS()
class RAYNETAB_TEST13_API UGameMain : public UUserWidget
{
	GENERATED_BODY ()

public:

	UPROPERTY ( BlueprintReadWrite, Category = "Players" )
		TWeakObjectPtr<AGamePlayer> Me;

	UPROPERTY ( BlueprintReadWrite, Category = "Players" )
		TWeakObjectPtr<AGamePlayer> Enemy;

	UPROPERTY ( BlueprintReadWrite, Category = "Players" )
		bool MeGoingFirst = true;

	TSharedPtr<ChessBoard> chessBoard;

	UFUNCTION ( BlueprintCallable , Category = "Functions" )
		void init ();

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool Confirm ( TArray<ShowType> Setting_M, TArray<ShowType> Setting_E );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		TArray<FPawnType> Refresh ();

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		void ShowMoveablePoint (FVector2D from);

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool ShowMovePointToServer ();

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		void ShowMoveablePoint_Card ( int32 PlayerID, TerminalCard card );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		void ClearMovePoint ();

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool LineBoost_BP (int32 playerID, FVector2D place );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool FireWall_BP ( int32 playerID, FVector2D place );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool VirusCheck_BP ( int32 playerID, FVector2D place );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool NotFoundSwap_BP ( int32 playerID, FVector2D from, FVector2D to );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool NotFoundNoSwap_BP ( int32 playerID, FVector2D from, FVector2D to );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool Move ( FVector2D from, FVector2D to );

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool MoveToServer ( FVector2D from );

};
