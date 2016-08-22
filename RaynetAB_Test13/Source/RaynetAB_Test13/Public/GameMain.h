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
		bool Confirm (TArray<TEnumAsByte<ShowType>> Setting);

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		TArray<FPawnType> Refresh ();

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		void ShowMoveablePoint (FVector2D from);

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		bool ShowMovePointToServer ();

	UFUNCTION ( BlueprintCallable, Category = "Functions" )
		void ShowMoveablePoint_Card ( TEnumAsByte<TerminalCard> card );
};
