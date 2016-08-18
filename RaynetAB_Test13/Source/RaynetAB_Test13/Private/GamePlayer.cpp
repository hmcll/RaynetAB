// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "GamePlayer.h"


// Called when the game starts or when spawned
void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGamePlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

AGamePlayer::AGamePlayer () {
	AGamePlayer ( 0 );
}

AGamePlayer::AGamePlayer ( int32 playerID ):
	_playerID(playerID){
	PrimaryActorTick.bCanEverTick = false;

	_terminal.Init ( false, 4 );
}

void AGamePlayer::setEnemy ( TWeakObjectPtr<AGamePlayer> EnemyPlayerID ) {
	_enemy = EnemyPlayerID;
}

TWeakObjectPtr<AGamePlayer> AGamePlayer::getEnemy () {
	return _enemy;
}

bool AGamePlayer::Win () {
	if ( _enemy->_server_L + _dataBase_L == 4 )
		return true;
	if ( _enemy->_dataBase_V == 4 )
		return true;
	return false;
}

bool AGamePlayer::addToServer ( const PawnType Type ) {
	switch ( Type ) {
	case PawnType::Link:
		_server_L++;
		break;
	case PawnType::Virus:
		_server_V++;
		break;
	case PawnType::Null:
	default:
		return false;
		break;
	}
	return true;
}

bool AGamePlayer::addToDataBase ( PawnType Type ) {
	switch ( Type ) {
	case PawnType::Link:
		_dataBase_L++;
		break;
	case PawnType::Virus:
		_dataBase_V++;
		break;
	case PawnType::Null:
	default:
		return false;
		break;
	}
	return true;
}

bool AGamePlayer::getTerminalUse ( TerminalCard card ) {
	return _terminal[int ( card )];
}

void AGamePlayer::setTerminalUse ( TerminalCard card, bool state ) {
	_terminal[int ( card )] = state;
}



