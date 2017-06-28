// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "RaynetAB_Test13PlayerState.h"


bool ARaynetAB_Test13PlayerState::Win() {
	return false;
}

void ARaynetAB_Test13PlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaynetAB_Test13PlayerState, roomNumber);
	DOREPLIFETIME(ARaynetAB_Test13PlayerState, isHost);
}