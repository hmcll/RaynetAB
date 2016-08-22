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

bool UGameMain::Confirm ( TArray<TEnumAsByte<ShowType>> Setting ) {
	if ( Setting.Num () != 8 ) return false;
	TArray<ShowType> Converted_Setting;
	for ( int i = 0; i < 8; i++ ) {
		Converted_Setting.Add( Setting[i].GetValue ());
	}
	if(!chessBoard->SetPawn_Y ( Converted_Setting ))return false;
	//init of Pawn_B needed
	if (!chessBoard->SetPawn_B ( Converted_Setting ) )return false;
	return true;
}

TArray<FPawnType>  UGameMain::Refresh () {
	return chessBoard->Refresh ();
}

void UGameMain::ShowMoveablePoint ( FVector2D from ) {
	chessBoard->ShowMoveablePoint (from);
}

bool UGameMain::ShowMovePointToServer () {
	return chessBoard->getMovePointServer ();
}

void UGameMain::ShowMoveablePoint_Card ( TEnumAsByte<TerminalCard> card ) {

}