// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "GameMain.h"


void UGameMain::init () {
	Me = (AGamePlayer*) GetWorld ()->SpawnActor ( AGamePlayer::StaticClass () );
	Enemy = (AGamePlayer*) GetWorld ()->SpawnActor ( AGamePlayer::StaticClass () );
	Me->setEnemy ( Enemy );
	Enemy->setEnemy ( Me );
	Me->setID ( 0 );
	Enemy->setID ( 1 );
	chessBoard = TSharedPtr<ChessBoard> ( new ChessBoard ( Me, Enemy ) );
}

bool UGameMain::Confirm ( TArray<ShowType> Setting_M, TArray<ShowType> Setting_E ) {
	if ( Setting_M.Num ()+Setting_E.Num () != 16 ) return false;

	if ( !chessBoard->SetPawn_Y ( Setting_M ) )return false;
	if ( !chessBoard->SetPawn_B ( Setting_E ) )return false;
	return true;
}

TArray<FPawnType>  UGameMain::Refresh () {
	return chessBoard->Refresh ();
}

void UGameMain::ShowMoveablePoint ( FVector2D from ) {
	chessBoard->clearMovePoint ();
	chessBoard->ShowMoveablePoint ( from );
}

bool UGameMain::ShowMovePointToServer () {
	return chessBoard->getMovePointServer ();
}

void UGameMain::ShowMoveablePoint_Card ( int32 PlayerID, TEnumAsByte<TerminalCard> card ) {
	chessBoard->clearMovePoint ();
	chessBoard->ShowMoveablePoint_Card ( PlayerID, card );
}

void UGameMain::ClearMovePoint () {
	chessBoard->clearMovePoint ();
}

bool UGameMain::LineBoost_BP ( int32 playerID, FVector2D place ) {
	return chessBoard->LineBoost ( playerID == 0 ? Me : Enemy, place );
}

bool UGameMain::FireWall_BP ( int32 playerID, FVector2D place ) {
	return chessBoard->FireWall ( playerID == 0 ? Me : Enemy, place );
}

bool UGameMain::VirusCheck_BP ( int32 playerID, FVector2D place ) {
	return chessBoard->VirusCheck ( playerID == 0 ? Me : Enemy, place );
}

bool UGameMain::NotFoundSwap_BP ( int32 playerID, FVector2D from, FVector2D to ) {
	return chessBoard->NotFoundSwap ( playerID == 0 ? Me : Enemy, from, to );
}

bool UGameMain::NotFoundNoSwap_BP ( int32 playerID, FVector2D from, FVector2D to ) {
	return chessBoard->NotFoundNoSwap ( playerID == 0 ? Me : Enemy, from, to );
}

bool  UGameMain::Move ( FVector2D from, FVector2D to ) {
	return chessBoard->Move ( from, to );
}

bool  UGameMain::MoveToServer ( FVector2D from ) {
	return chessBoard->MoveToServer ( from );
}