// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "ChessBoard.h"
#include "GameMain_Map.generated.h"

/**
 * 
 */
UCLASS()
class RAYNETAB_TEST13_API AGameMain_Map : public ALevelScriptActor
{
	GENERATED_BODY ()
public:

	UPROPERTY ( BlueprintReadWrite ,Category = "Players")
		TWeakObjectPtr<AGamePlayer> Me;

	UPROPERTY ( BlueprintReadWrite, Category = "Players" )
		TWeakObjectPtr<AGamePlayer> Enemy;

	void BeginPlay () override;
	
	
};
