// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "GameMain.h"


void UGameMain::init () {
	Me = (AGamePlayer*) GetWorld ()->SpawnActor ( AGamePlayer::StaticClass () );
	Enemy = (AGamePlayer*) GetWorld ()->SpawnActor ( AGamePlayer::StaticClass () );
	Me->setEnemy ( Enemy );
	Enemy->setEnemy ( Me );
	chessBoard = TSharedPtr<ChessBoard> ( new ChessBoard ( Me, Enemy ) );
}
