// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "GameMain_Map.h"



void AGameMain_Map::BeginPlay () {
	Me = (AGamePlayer*)GetWorld ()->SpawnActor ( AGamePlayer::StaticClass ());
	Enemy = (AGamePlayer*) GetWorld ()->SpawnActor ( AGamePlayer::StaticClass () );
	Me->setEnemy ( Enemy );
	Enemy->setEnemy ( Me );
	AfterBeginPlay ();
}
