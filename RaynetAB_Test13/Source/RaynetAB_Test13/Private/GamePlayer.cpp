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

AGamePlayer::AGamePlayer ()
	:
	_playerID ( 0 ) {
	PrimaryActorTick.bCanEverTick = false;

	_terminal.Init ( false, 4 );

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

bool AGamePlayer::addToServer ( const ShowType Type ) {
	switch ( Type ) {
	case ShowType::LinkYL:
		setTerminalUse ( TerminalCard::LineBoost, true );
	case ShowType::LinkY:
		_server_L++;
		break;
	case ShowType::VirusYL:
		setTerminalUse ( TerminalCard::LineBoost, true );
	case ShowType::VirusY:
		_server_V++;
		break;
	default:
		return false;
		break;
	}
	return true;
}

bool AGamePlayer::addToDataBase ( ShowType Type ) {
	switch ( Type ) {
	case ShowType::LinkYL:
		setTerminalUse ( TerminalCard::LineBoost, true );
	case ShowType::LinkY:
		_dataBase_L++;
		break;
	case ShowType::VirusYL:
		setTerminalUse ( TerminalCard::LineBoost, true );
	case ShowType::VirusY:
		_dataBase_V++;
		break;
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

void AGamePlayer::setID ( int32 ID ) {
	_playerID = ID;
}
