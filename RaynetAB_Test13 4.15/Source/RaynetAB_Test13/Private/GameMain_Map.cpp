// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "GameMain_Map.h"



void AGameMain_Map::BeginPlay () {
	GSystemResolution.RequestResolutionChange ( 540, 960, EWindowMode::Windowed );
	AfterBeginPlay ();
}