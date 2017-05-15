// Copyright(C) 2015 - 2016  Raynet AB Development Team

#include "RaynetAB_Test13.h"
#include "RayneyAB_Test13GameState.h"


void ARayneyAB_Test13GameState::Server_SetPawn_Arrangement_Implementation ( bool Offensive,const TArray<ShowType>& Setting ) {

}

void ARayneyAB_Test13GameState::Server_Confirm_Implementation () {
	if ( Flag_OnesideFinished ) {

	}
	else {
		Flag_OnesideFinished = true;
	}
}

ARayneyAB_Test13GameState::ARayneyAB_Test13GameState () {
	bReplicates = true;
}

void ARayneyAB_Test13GameState::Server_Move_Implementation ( FMove_C move ) {

}

void ARayneyAB_Test13GameState::Server_Win_Implementation ( bool EnemyWinState ) {

}

bool ARayneyAB_Test13GameState::Server_SetPawn_Arrangement_Validate ( bool Offensive,const TArray<ShowType>& Setting ) {
	return true;
}

bool ARayneyAB_Test13GameState::Server_Confirm_Validate () {
	return true;
}

bool ARayneyAB_Test13GameState::Server_Move_Validate ( FMove_C move ) {
	return true;
}

bool ARayneyAB_Test13GameState::Server_Win_Validate ( bool EnemyWinState ) {
	return true;
}

void ARayneyAB_Test13GameState::GetLifetimeReplicatedProps ( TArray< FLifetimeProperty > & OutLifetimeProps ) const{
	Super::GetLifetimeReplicatedProps ( OutLifetimeProps );
	DOREPLIFETIME ( ARayneyAB_Test13GameState, Flag_OnesideFinished );
}