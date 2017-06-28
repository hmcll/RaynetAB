// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Enums_and_Structs.h"
#include "RaynetAB_Test13PlayerState.generated.h"

class ARaynetAB_Test13GameState;
/**
 * 
 */
UCLASS()
class RAYNETAB_TEST13_API ARaynetAB_Test13PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
		int32 roomNumber;

	UPROPERTY(Replicated)
		int32 id;
	
	UPROPERTY(Replicated, BlueprintReadOnly)
		bool isHost;
	
	
	UFUNCTION(BlueprintCallable, Category = "default")
		bool Win();

};
