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

	TSharedPtr<ChessBoard> chessBoard;

	UFUNCTION ( BlueprintCallable , Category = "Functions" )
		void init ();
};
