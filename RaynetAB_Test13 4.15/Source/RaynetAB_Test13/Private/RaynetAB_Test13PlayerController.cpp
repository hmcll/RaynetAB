// Copyright(C) 2015 - 2016  Raynet AB Development Team

#include "RaynetAB_Test13.h"
#include "RaynetAB_Test13GameMode.h"
#include "RaynetAB_Test13PlayerController.h"

bool ARaynetAB_Test13PlayerController::ShowMovePointToServer() {
	ShowMovePointToServer_SV();
	return Cast<ARaynetAB_Test13GameState>(GetWorld()->GetGameState())->MovePointToServer;
}

void ARaynetAB_Test13PlayerController::GotEnemyFinished_Implementation() {
	auto a = Cast<ARaynetAB_Test13GameState>(GetWorld()->GetGameState());
	a->RefreshState = false;
	ResetGotUpdate.Broadcast();
}

bool ARaynetAB_Test13PlayerController::GotEnemyFinished_Validate() {
	return true;
}

void ARaynetAB_Test13PlayerController::GotUpdate_Implementation() {
	auto a = Cast<ARaynetAB_Test13GameState>(GetWorld()->GetGameState());
	a->EnemyFinishedState = false;
	ResetGotUpdate.Broadcast();
}
	
bool ARaynetAB_Test13PlayerController::GotUpdate_Validate() {
	return true;
}

void ARaynetAB_Test13PlayerController::Confirm_Implementation(const TArray<ShowType>& Setting) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->Confirm(_PlayerState->roomNumber, _PlayerState->id, Setting);
	
}

void ARaynetAB_Test13PlayerController::Refresh_Implementation() {
	
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->Refresh(_PlayerState->roomNumber);
}

void ARaynetAB_Test13PlayerController::ShowMoveablePoint_Implementation(FVector2D from) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->ShowMoveablePoint(_PlayerState->roomNumber, from);
}

void ARaynetAB_Test13PlayerController::ShowMovePointToServer_SV_Implementation() {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->ShowMovePointToServer(_PlayerState->roomNumber);
}

void ARaynetAB_Test13PlayerController::ShowMoveablePoint_Card_Implementation(TerminalCard card) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->ClearMovePoint(_PlayerState->roomNumber);
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->ShowMoveablePoint_Card(_PlayerState -> roomNumber, _PlayerState->id, card, _PlayerState->_terminal);
}

void ARaynetAB_Test13PlayerController::ClearMovePoint_Implementation() {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->ClearMovePoint(_PlayerState->roomNumber);
}

void ARaynetAB_Test13PlayerController::LineBoost_BP_Implementation(FVector2D place) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->LineBoost(_PlayerState->roomNumber, _PlayerState->id, place, _PlayerState->_terminal[(int32) TerminalCard::LineBoost]);
}

void ARaynetAB_Test13PlayerController::FireWall_BP_Implementation(FVector2D place) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->FireWall(_PlayerState->roomNumber, _PlayerState->id, place, _PlayerState->_terminal[(int32) TerminalCard::Firewall]);
}

void ARaynetAB_Test13PlayerController::VirusCheck_BP_Implementation(FVector2D place) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->VirusCheck(_PlayerState->roomNumber, _PlayerState->id, place);
}

void ARaynetAB_Test13PlayerController::NotFoundSwap_BP_Implementation(FVector2D from, FVector2D to) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->NotFoundSwap(_PlayerState->roomNumber, _PlayerState->id, from, to);
}

void ARaynetAB_Test13PlayerController::NotFoundNoSwap_BP_Implementation(FVector2D from, FVector2D to) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->NotFoundNoSwap(_PlayerState->roomNumber, _PlayerState->id, from, to);
}

void ARaynetAB_Test13PlayerController::Move_Implementation(FVector2D from, FVector2D to) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->Move(_PlayerState->roomNumber, from, to);
}

void ARaynetAB_Test13PlayerController::MoveToServer_Implementation(FVector2D from) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->MoveToServer(_PlayerState->roomNumber, from);
}

void ARaynetAB_Test13PlayerController::Server_Move_Implementation(FMove_C move) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->Server_Move(move);
}

void ARaynetAB_Test13PlayerController::Server_Win_Implementation(bool HostWon) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->Server_Win(HostWon);
}

void ARaynetAB_Test13PlayerController::AfterPostLogin_Implementation() {
	CreateUI();
}

void ARaynetAB_Test13PlayerController::changeState_Implementation(EGameState StateTo) {
	Cast<ARaynetAB_Test13GameMode>(GetWorld()->GetAuthGameMode())->changeState(StateTo);
}

void ARaynetAB_Test13PlayerController::SetHostGoingFirst_Implementation(bool HostGoingFirst) {
	Cast<ARaynetAB_Test13GameState>(GetWorld()->GetGameState())->Flag_HostGoingFirst = HostGoingFirst;
}


bool ARaynetAB_Test13PlayerController::Refresh_Validate() {
	return true;
}

bool ARaynetAB_Test13PlayerController::ShowMovePointToServer_SV_Validate() {
	return true;
}


bool ARaynetAB_Test13PlayerController::AfterPostLogin_Validate() {
	return true;
}

bool ARaynetAB_Test13PlayerController::Confirm_Validate(const TArray<ShowType>& Setting) {
	return true;
}

bool ARaynetAB_Test13PlayerController::ShowMoveablePoint_Validate(FVector2D from) {
	return true;
}

bool ARaynetAB_Test13PlayerController::ShowMoveablePoint_Card_Validate(TerminalCard card) {
	return true;
}

bool ARaynetAB_Test13PlayerController::ClearMovePoint_Validate() {
	return true;
}

bool ARaynetAB_Test13PlayerController::LineBoost_BP_Validate(FVector2D place) {
	return true;
}

bool ARaynetAB_Test13PlayerController::FireWall_BP_Validate(FVector2D place) {
	return true;
}

bool ARaynetAB_Test13PlayerController::VirusCheck_BP_Validate(FVector2D place) {
	return true;
}

bool ARaynetAB_Test13PlayerController::NotFoundSwap_BP_Validate(FVector2D from, FVector2D to) {
	return true;
}

bool ARaynetAB_Test13PlayerController::NotFoundNoSwap_BP_Validate(FVector2D from, FVector2D to) {
	return true;
}

bool ARaynetAB_Test13PlayerController::Move_Validate(FVector2D from, FVector2D to) {
	return true;
}

bool ARaynetAB_Test13PlayerController::MoveToServer_Validate(FVector2D from) {
	return true;
}

bool ARaynetAB_Test13PlayerController::changeState_Validate(EGameState StateTo) {
	return true;
}

bool ARaynetAB_Test13PlayerController::Server_Move_Validate(FMove_C move) {
	return true;
}

bool ARaynetAB_Test13PlayerController::Server_Win_Validate(bool HostWon) {
	return true;
}

bool ARaynetAB_Test13PlayerController::SetHostGoingFirst_Validate(bool HostGoingFirst) {
	return true;
}


void ARaynetAB_Test13PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaynetAB_Test13PlayerController, _PlayerState);
}
//cholscholomance