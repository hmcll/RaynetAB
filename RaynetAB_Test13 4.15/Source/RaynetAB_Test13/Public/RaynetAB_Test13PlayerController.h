// Copyright(C) 2015 - 2016  Raynet AB Development Team
#pragma once

#include "GameFramework/PlayerController.h"
#include "Enums_and_Structs.h"
#include "RaynetAB_Test13GameState.h"
#include "RaynetAB_Test13PlayerState.h"
#include "RaynetAB_Test13PlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetGotUpdate);

UCLASS()
class RAYNETAB_TEST13_API ARaynetAB_Test13PlayerController: public APlayerController {
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Dispatchers")
		FResetGotUpdate ResetGotUpdate;

	UPROPERTY(Replicated, BlueprintReadOnly)
		ARaynetAB_Test13PlayerState* _PlayerState;

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void Refresh();

	UFUNCTION(Server, WithValidation, Reliable)
		void Refresh_SV();
	
	UFUNCTION(Server, WithValidation, Reliable)
		void ShowMovePointToServer_SV();

	UFUNCTION(BlueprintCallable, Category = "Functions")
		bool ShowMovePointToServer();

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void GotUpdate();

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void SetHostGoingFirst(bool HostGoingFirst);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void Confirm(const TArray<ShowType>& Setting);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void ShowMoveablePoint(FVector2D from);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void ShowMoveablePoint_Card(TerminalCard card);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void ClearMovePoint();

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void LineBoost_BP(FVector2D place);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void FireWall_BP(FVector2D place);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void VirusCheck_BP(FVector2D place);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void NotFoundSwap_BP(FVector2D from, FVector2D to);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void NotFoundNoSwap_BP(FVector2D from, FVector2D to);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void Move(FVector2D from, FVector2D to);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void MoveToServer(FVector2D from);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void changeState(EGameState StateTo);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void Server_Move(FMove_C move);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Functions")
		void Server_Win(bool HostWon);

	UFUNCTION(BlueprintImplementableEvent, Category = "Functions")
		void CreateUI();

	UFUNCTION(Client, Reliable, WithValidation)
		void AfterPostLogin();

};

