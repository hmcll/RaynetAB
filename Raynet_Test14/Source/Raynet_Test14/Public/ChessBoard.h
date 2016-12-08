// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GamePlayer.h"

/**
 *
 */



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
	TWeakObjectPtr<AGamePlayer> _player;
	ShowType _type;
	bool _IsMovePoint = false;
public:
	virtual FPawnType toFPawnType () = 0;
	virtual ~Pawn ();
	//is able to move
	void setMovePoint ( const bool state );
	bool isMovePoint () const;
	virtual bool isMoveable () const = 0;
	ShowType getType () const;
	virtual	TWeakObjectPtr<AGamePlayer> getPlayer () const;
};
/*
Common Features of Link and Virus
*/
class Moveable: public Pawn {
protected:
	bool _IsLineBoosting = false;
	bool _IsShowingOff = false;
	bool _IsSelected = false;
public:
	bool isMoveable () const override;
	bool isLineBoosting () const;
	void setLineBoost ( const bool state );
	bool isShowingOff () const;
	void setShowingOff ( const bool state );
	bool isSelected () const;
	void setSelected ( const bool state );
};

/*
Link card
*/

class Link: public Moveable {
public:
	FPawnType toFPawnType () override;
	Link ( TWeakObjectPtr<AGamePlayer> player );
	~Link () override;
};

/*
Virus card
*/

class Virus: public Moveable {
public:
	FPawnType toFPawnType () override;
	Virus ( TWeakObjectPtr<AGamePlayer>  player );
	~Virus () override;
};

/*
Empty Place or Firewall
*/

class Null: public Pawn {
private:
	bool _IsFireWallOn = false;
	TWeakObjectPtr<AGamePlayer> FireWallPlayer;
public:
	FPawnType toFPawnType () override;
	Null ();
	void setFirewall ( const bool state );
	bool isFirewallOn () const;	
	TWeakObjectPtr<AGamePlayer> getPlayer () const override;
	bool setFireWallPlayer ( TWeakObjectPtr<AGamePlayer> player);
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
	bool SetPawn_Y ( TArray<ShowType> Setting );
	bool SetPawn_B ( TArray<ShowType> Setting );
	bool getMovePointServer ();
	void clearMovePoint ();
	bool LineBoost ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool FireWall ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool VirusCheck ( TWeakObjectPtr<AGamePlayer> player, Place place );
	bool NotFoundSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to );
	bool NotFoundNoSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to );
	bool ShowMoveablePoint ( Place pawn );
	void ShowMoveablePoint_Card ( int32 PlayerID, TerminalCard card );
	bool Move ( Place from, Place to );
	bool MoveToServer ( Place from );
	TArray<FPawnType> Refresh ();
};