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


/*
A place on the Board
*/

class Pawn {
protected:
	State _state = State::OnLine;
	TWeakObjectPtr<AGamePlayer> _player;
	PawnType _type;
public:
	virtual ~Pawn ();
	//is able to move
	virtual bool isMoveable () const = 0;
	PawnType getType () const;
	virtual	TWeakObjectPtr<AGamePlayer> getPlayer ()const;
};
/*
Common Features of Link and Virus
*/
class Moveable: public Pawn {
	bool _IsLineBoosting = false;
	bool _IsShowingOff = false;
public:
	bool isMoveable () const override;
	bool isLineboosting () const;
	void setLineBoost ( const bool state );
	bool isShowingOff () const;
	void setShowingOff ( const bool state );
};

/*
Link card
*/

class Link: public Moveable {
public:
	Link ( TWeakObjectPtr<AGamePlayer>  player );
	~Link ()											override;
};

/*
Virus card
*/

class Virus: public Moveable {
public:
	Virus ( TWeakObjectPtr<AGamePlayer>  player );
	~Virus ()										override;
};

/*
Empty Place or Firewall
*/

class Null: public Pawn {
private:
	bool											FireWallOn;
public:
	Null ();
	void setFirewall ( const bool state );
	bool isFirewallOn () const;
	TWeakObjectPtr<AGamePlayer> getPlayer () const override;
	bool isMoveable () const override;
	~Null () override;
};

class RAYNETAB_TEST13_API ChessBoard {
	// left down cornor is 0,0 up right is 7,7
	Board		chessBoard;

	TWeakObjectPtr<AGamePlayer> _Me;
	TWeakObjectPtr<AGamePlayer> _Enemy;
public:
	ChessBoard ( TWeakObjectPtr<AGamePlayer> Me, TWeakObjectPtr<AGamePlayer> Enemy);
	bool								SetPawn_Y ( int Pattern );
	bool								SetPawn_B ( int Pattern );
	const Board&						getChessBoard ();
	bool								LineBoost ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool								FireWall ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool								VirusCheck ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool								NotFoundSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to );
	bool								NotFoundNoSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to );
	TArray<Place>						ShowMoveablePoint ( Place pawn );
	bool								Move ( Place from, Place to );
	bool								MoveToServer ( Place from );
};