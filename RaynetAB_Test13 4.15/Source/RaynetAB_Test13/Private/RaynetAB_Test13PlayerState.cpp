// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "RaynetAB_Test13PlayerState.h"


bool ARaynetAB_Test13PlayerState::Win() {
	if( _enemy->_server_L + _dataBase_L == 4 )
		return true;
	if( _enemy->_dataBase_V == 4 )
		return true;
	return false;
}

bool ARaynetAB_Test13PlayerState::addToServer(bool isShowingOff, bool islineboosting, const ShowType Type) {
	switch( Type ) {
	case ShowType::LinkE:
	case ShowType::LinkM:
		_server_L++;
		Showingoff = isShowingOff ? ServerShowingOff::Link : Showingoff;
		break;
	case ShowType::VirusE:
	case ShowType::VirusM:
		_server_V++;
		Showingoff = isShowingOff ? ServerShowingOff::Virus : Showingoff;
		break;
	default:
		return false;
		break;
	}
	if( islineboosting )_enemy->setTerminalUse(TerminalCard::LineBoost, TERMINALCARD_UNUSED);
	return true;
}

bool ARaynetAB_Test13PlayerState::addToDataBase(bool islineboosting, ShowType Type) {
	switch( Type ) {
	case ShowType::LinkE:
	case ShowType::LinkM:
		_dataBase_L++;
		break;
	case ShowType::VirusE:
	case ShowType::VirusM:
		_dataBase_V++;
		break;
	default:
		return false;
		break;
	}
	if( islineboosting ) _enemy->setTerminalUse(TerminalCard::LineBoost, TERMINALCARD_UNUSED);
	return true;
}

bool ARaynetAB_Test13PlayerState::getTerminalUse(TerminalCard card) {
	return _terminal[int(card)];
}

void ARaynetAB_Test13PlayerState::setTerminalUse(TerminalCard card, bool state) {
	_terminal[int(card)] = state;
}



void ARaynetAB_Test13PlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaynetAB_Test13PlayerState, roomNumber);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, _enemy);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, _server_V);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, _server_L);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, _dataBase_V);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, _dataBase_L);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, _terminal);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, Showingoff);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, isHost);
}