// Copyright(C) 2015 - 2016  Raynet AB Development Team

#include "RaynetAB_Test13.h"
#include "RaynetAB_Test13GameState.h"



void ARaynetAB_Test13GameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		
	DOREPLIFETIME(ARaynetAB_Test13GameState, Refresh);
	DOREPLIFETIME(ARaynetAB_Test13GameState, RefreshState);
	DOREPLIFETIME(ARaynetAB_Test13GameState, Flag_HostWon);
	DOREPLIFETIME(ARaynetAB_Test13GameState, Flag_HostGoingFirst);
	DOREPLIFETIME(ARaynetAB_Test13GameState, MoveStack);
	DOREPLIFETIME(ARaynetAB_Test13GameState, _GameState);
}

