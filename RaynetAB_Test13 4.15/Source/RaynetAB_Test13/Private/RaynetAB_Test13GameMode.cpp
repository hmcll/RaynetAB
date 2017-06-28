// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "RaynetAB_Test13GameMode.h"

void ARaynetAB_Test13GameMode::PostLogin(APlayerController * NewPlayer) {
	Super::PostLogin(NewPlayer);
	if( HasAuthority() ) {
		int id = 0;
		if( ( id = Playerstack.Add(Cast<ARaynetAB_Test13PlayerController>(NewPlayer)) ) % 2 == 1 ) {
			auto player1 = Cast<ARaynetAB_Test13PlayerState>(Playerstack[0]->PlayerState);
			auto player2 = Cast<ARaynetAB_Test13PlayerState>(Playerstack[1]->PlayerState);
			check(player1);
			check(player2);
			player1->roomNumber = id / 2;
			player2->roomNumber = id / 2;
			player1->id = 1;
			player2->id = 2;
			player1->isHost = true;
			player2->isHost = false;
			Playerstack[0]->_PlayerState = player1;
			Playerstack[1]->_PlayerState = player2;
			CreateNewRoom(id / 2);
			Cast<ARaynetAB_Test13GameState>(GameState)->_GameState = EGameState::Starting;
			
			Cast<ARaynetAB_Test13PlayerController>(Playerstack[0])->AfterPostLogin();
			Cast<ARaynetAB_Test13PlayerController>(Playerstack[1])->AfterPostLogin();
		}
	}
}



void ARaynetAB_Test13GameMode::CreateNewRoom_Implementation(int32 id) {
	Rooms.Insert(NewObject<UChessBoard>(), id);
}

void ARaynetAB_Test13GameMode::Server_Move_Implementation(FMove_C move, RoundRefreshState RoundAfter) {
	Cast<ARaynetAB_Test13GameState>(GameState)->MoveStack.Add(move);
	Cast<ARaynetAB_Test13GameState>(GameState)->roundRefresh = RoundAfter;
}

void ARaynetAB_Test13GameMode::Server_Win_Implementation(bool HostWon) {
	Cast<ARaynetAB_Test13GameState>(GameState)->Flag_HostWon = HostWon;
	Cast<ARaynetAB_Test13GameState>(GameState)->_GameState = EGameState::Ending;
}

void ARaynetAB_Test13GameMode::Confirm_Implementation(int32 roomNumber, int32 player, const TArray<ShowType>& Setting) {
	if( player == 0 )
		Rooms[roomNumber]->SetPawn_1(Setting);
	else
		Rooms[roomNumber]->SetPawn_2(Setting);

	if( Cast<ARaynetAB_Test13GameState>(GameState)->_GameState == EGameState::Setting_BothNotFinished ) {
		Cast<ARaynetAB_Test13GameState>(GameState)->_GameState = EGameState::Setting_OneSideNotFinished;
	}
	else {
		Cast<ARaynetAB_Test13GameState>(GameState)->_GameState = EGameState::Setting_BothFinished;
	}
}

void ARaynetAB_Test13GameMode::Refresh_Implementation(int32 playerid,int32 roomNumber) {
	auto st = Cast<ARaynetAB_Test13GameState>(GameState);
	Cast<ARaynetAB_Test13GameState>(GameState)->Refresh = Rooms[roomNumber]->Refresh(playerid);
	Cast<ARaynetAB_Test13GameState>(GameState)->RefreshState = true;
	if( playerid == 1 ) {
		Cast<ARaynetAB_Test13GameState>(GameState)->RefreshPlayer = *Rooms[roomNumber]->player1;
		Cast<ARaynetAB_Test13GameState>(GameState)->RefreshPlayer_Enemy = *Rooms[roomNumber]->player2;
	}
	else {

		Cast<ARaynetAB_Test13GameState>(GameState)->RefreshPlayer = *Rooms[roomNumber]->player2;
		Cast<ARaynetAB_Test13GameState>(GameState)->RefreshPlayer_Enemy = *Rooms[roomNumber]->player1;
	}
}

void ARaynetAB_Test13GameMode::ShowMoveablePoint_Implementation(int32 roomNumber, FVector2D from) {
	Rooms[roomNumber]->clearMovePoint();
	Rooms[roomNumber]->ShowMoveablePoint(from);
}

void ARaynetAB_Test13GameMode::ShowMovePointToServer_Implementation(int32 roomNumber) {
	Cast<ARaynetAB_Test13GameState>(GameState)->MovePointToServer = Rooms[roomNumber]->getMovePointServer();
}

void ARaynetAB_Test13GameMode::ShowMoveablePoint_Card_Implementation(int32 roomNumber, int32 playerID, TerminalCard card) {
	Rooms[roomNumber]->clearMovePoint();
	Rooms[roomNumber]->ShowMoveablePoint_Card(playerID, card);
}

void ARaynetAB_Test13GameMode::ClearMovePoint_Implementation(int32 roomNumber) {
	Rooms[roomNumber]->clearMovePoint();
}

void ARaynetAB_Test13GameMode::LineBoost_Implementation(int32 roomNumber, FVector2D place) {
	Rooms[roomNumber]->LineBoost( place);
}

void ARaynetAB_Test13GameMode::FireWall_Implementation(int32 roomNumber, int32 playerID, FVector2D place) {
	Rooms[roomNumber]->FireWall(playerID, place);
}

void ARaynetAB_Test13GameMode::VirusCheck_Implementation(int32 roomNumber, int32 playerID, FVector2D place) {
	Rooms[roomNumber]->VirusCheck(playerID, place);
}

void ARaynetAB_Test13GameMode::NotFoundSwap_Implementation(int32 roomNumber, int32 playerID, FVector2D from, FVector2D to) {
	Rooms[roomNumber]->NotFoundSwap(playerID, from, to);
}

void ARaynetAB_Test13GameMode::NotFoundNoSwap_Implementation(int32 roomNumber, int32 playerID, FVector2D from, FVector2D to) {
	Rooms[roomNumber]->NotFoundNoSwap(playerID, from, to);
}

void ARaynetAB_Test13GameMode::Move_Implementation(int32 roomNumber, FVector2D from, FVector2D to) {
	Rooms[roomNumber]->Move(from, to);
}

void ARaynetAB_Test13GameMode::MoveToServer_Implementation(int32 roomNumber, FVector2D from) {
	Rooms[roomNumber]->MoveToServer(from);
}

void ARaynetAB_Test13GameMode::changeState_Implementation(EGameState stateTo) {
	Cast<ARaynetAB_Test13GameState>(GameState)->_GameState = stateTo;
}


bool ARaynetAB_Test13GameMode::Server_Move_Validate(FMove_C move, RoundRefreshState to) {
	return true;
}

bool ARaynetAB_Test13GameMode::Server_Win_Validate(bool HostWon) {
	return true;
}

bool ARaynetAB_Test13GameMode::changeState_Validate(EGameState stateTo) {
	return true;
}

bool ARaynetAB_Test13GameMode::Confirm_Validate(int32 roomNumber, int32 player, const TArray<ShowType>& Setting) {
	return true;
}

bool ARaynetAB_Test13GameMode::Refresh_Validate(int32 playerid,int32 roomNumber) {
	return true;
}

bool ARaynetAB_Test13GameMode::CreateNewRoom_Validate(int32 id) {
	return true;
}

bool ARaynetAB_Test13GameMode::ShowMoveablePoint_Validate(int32 roomNumber, FVector2D from) {
	return true;
}

bool ARaynetAB_Test13GameMode::ShowMoveablePoint_Card_Validate(int32 roomNumber, int32 playerID, TerminalCard card) {
	return true;
}

bool ARaynetAB_Test13GameMode::ClearMovePoint_Validate(int32 roomNumber) {
	return true;
}

bool ARaynetAB_Test13GameMode::LineBoost_Validate(int32 roomNumber, FVector2D place) {
	return true;
}

bool ARaynetAB_Test13GameMode::FireWall_Validate(int32 roomNumber, int32 playerID, FVector2D place) {
	return true;
}

bool ARaynetAB_Test13GameMode::VirusCheck_Validate(int32 roomNumber, int32 playerID, FVector2D place) {
	return true;
}

bool ARaynetAB_Test13GameMode::NotFoundSwap_Validate(int32 roomNumber, int32 playerID, FVector2D from, FVector2D to) {
	return true;
}

bool ARaynetAB_Test13GameMode::NotFoundNoSwap_Validate(int32 roomNumber, int32 playerID, FVector2D from, FVector2D to) {
	return true;
}

bool ARaynetAB_Test13GameMode::Move_Validate(int32 roomNumber, FVector2D from, FVector2D to) {
	return true;
}

bool ARaynetAB_Test13GameMode::MoveToServer_Validate(int32 roomNumber, FVector2D from) {
	return true;
}

bool ARaynetAB_Test13GameMode::ShowMovePointToServer_Validate(int32 roomNumber) {
	return true;
}
