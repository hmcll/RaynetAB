// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Net/UnrealNetwork.h"
#include "RaynetAB_Test13PlayerController.h"
#include "RaynetAB_Test13GameMode.generated.h"


/**
 *
 */
UCLASS()
class RAYNETAB_TEST13_API ARaynetAB_Test13GameMode: public AGameModeBase {
	GENERATED_BODY()

public:

	TArray<ARaynetAB_Test13PlayerController*> Playerstack;

	TArray<UChessBoard*> Rooms;

	virtual void PostLogin(APlayerController * NewPlayer) override;
	
	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void Server_Move(FMove_C move);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void Server_Win(bool HostWon);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void changeState(EGameState stateTo);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void Confirm(int32 roomNumber, int32 player, const TArray<ShowType>& Setting);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void Refresh(int32 roomNumber);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void CreateNewRoom(int32 id);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void ShowMoveablePoint(int32 roomNumber, FVector2D from);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void ShowMovePointToServer(int32 roomNumber);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void ShowMoveablePoint_Card(int32 roomNumber, int32 playerID, TerminalCard card, const TArray<bool>& _terminal);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void ClearMovePoint(int32 roomNumber);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void LineBoost(int32 roomNumber, int32 playerID, FVector2D place, bool used);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void FireWall(int32 roomNumber, int32 playerID, FVector2D place, bool used);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void VirusCheck(int32 roomNumber, int32 playerID, FVector2D place);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void NotFoundSwap(int32 roomNumber, int32 playerID, FVector2D from, FVector2D to);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void NotFoundNoSwap(int32 roomNumber, int32 playerID, FVector2D from, FVector2D to);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void Move(int32 roomNumber, FVector2D from, FVector2D to);

	UFUNCTION(Server, WithValidation, Reliable, Category = "Functions")
		void MoveToServer(int32 roomNumber, FVector2D from);
};
