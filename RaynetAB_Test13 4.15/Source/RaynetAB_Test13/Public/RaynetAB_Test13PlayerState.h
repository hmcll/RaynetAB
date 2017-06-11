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
		ARaynetAB_Test13PlayerState* _enemy;

	UPROPERTY(Replicated, BlueprintReadOnly)
		int32 _server_V = 0;
	UPROPERTY(Replicated, BlueprintReadOnly)
		int32 _server_L = 0;
	UPROPERTY(Replicated, BlueprintReadOnly)
		int32 _dataBase_V = 0;
	UPROPERTY(Replicated, BlueprintReadOnly)
		int32 _dataBase_L = 0;


	UPROPERTY(Replicated, BlueprintReadOnly)
		TArray<bool>_terminal;
	UPROPERTY(Replicated, BlueprintReadOnly)
		ServerShowingOff Showingoff = ServerShowingOff::Null;

	UPROPERTY(Replicated, BlueprintReadOnly)
		bool isHost;


	bool addToServer(bool isShowingOff, bool islineboosting, ShowType Type);

	bool addToDataBase(bool islineboosting, ShowType Type);

	bool getTerminalUse(TerminalCard card);

	void setTerminalUse(TerminalCard card, bool state);
	
	UFUNCTION(BlueprintCallable, Category = "default")
		bool Win();

};
