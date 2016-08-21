// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GamePlayer.h"

/**
 *
 */

const bool TERMINALCARD_UNUSED = true;
const bool TERMINALCARD_USED = true;

//first = x second = y
typedef FVector2D Place;

class Pawn;

typedef TArray<TArray<TSharedPtr<Pawn>>> Board;

UENUM ( BlueprintType )
enum class State:uint8 {
	OnLine, Server, DataBase
};

UENUM ( BlueprintType )
enum class ShowType:uint8 {
	BackB,
	BackBL,
	BackBM,
	BackBLM,
	LinkBM,
	LinkBLM,
	LinkB,
	LinkBL,
	LinkY,
	LinkYL,
	LinkYO,
	LinkYLO,
	VirusB,
	VirusBL,
	VirusBM,
	VirusBLM,
	VirusY,
	VirusYL,
	VirusYO,
	VirusYLO,
	MovePioint,
	FireWall,
	Null,
};

/*
A place on the Board
*/

class Pawn {
protected:
	TWeakObjectPtr<AGamePlayer> _player;
	PawnType _type;
	bool _IsMovePoint;
public:
	virtual ShowType toEnum () = 0;
	virtual ~Pawn ();
	//is able to move
	void setMovePoint ( const bool state );
	bool isMovePoint () const;
	virtual bool isMoveable () const = 0;
	PawnType getType () const;
	virtual	TWeakObjectPtr<AGamePlayer> getPlayer () const;
};
/*
Common Features of Link and Virus
*/
class Moveable: public Pawn {
protected:
	bool _IsLineBoosting = false;
	bool _IsShowingOff = false;
public:
	bool isMoveable () const override;
	bool isLineBoosting () const;
	void setLineBoost ( const bool state );
	bool isShowingOff () const;
	void setShowingOff ( const bool state );
};

/*
Link card
*/

class Link: public Moveable {
public:
	ShowType toEnum () override;
	Link ( TWeakObjectPtr<AGamePlayer>  player );
	~Link () override;
};

/*
Virus card
*/

class Virus: public Moveable {
public:
	ShowType toEnum () override;
	Virus ( TWeakObjectPtr<AGamePlayer>  player );
	~Virus ()										override;
};

/*
Empty Place or Firewall
*/

class Null: public Pawn {
private:
	bool _IsFireWallOn;
public:
	ShowType toEnum () override;
	Null ();
	void setFirewall ( const bool state );
	bool isFirewallOn () const;	
	TWeakObjectPtr<AGamePlayer> getPlayer () const override;
	bool isMoveable () const override;
	~Null () override;
};

class ChessBoard {
	// left down cornor is 0,0 up right is 7,7
	Board chessBoard;

	TWeakObjectPtr<AGamePlayer> _Me;
	TWeakObjectPtr<AGamePlayer> _Enemy;
	
	bool MovePointServer = false;

public:
	ChessBoard ( TWeakObjectPtr<AGamePlayer> Me, TWeakObjectPtr<AGamePlayer> Enemy);
	bool SetPawn_Y ( int Pattern );
	bool SetPawn_B ( int Pattern );
	bool getMovePointServer ();
	bool LineBoost ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool FireWall ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool VirusCheck ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool NotFoundSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to );
	bool NotFoundNoSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to );
	bool ShowMoveablePoint ( Place pawn );
	bool Move ( Place from, Place to );
	bool MoveToServer ( Place from );
	TArray<TArray<ShowType>> Refresh ();
};