// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enums_and_Structs.h"
#include "ChessBoard.generated.h"

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
	int32 _player;
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
	virtual	int32 getPlayer () const;
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
	Link ( int32 player );
	~Link () override;
};

/*
Virus card
*/

class Virus: public Moveable {
public:
	FPawnType toFPawnType () override;
	Virus ( int32  player );
	~Virus () override;
};

/*
Empty Place or Firewall
*/

class Null: public Pawn {
private:
	bool _IsFireWallOn = false;
	bool _IsMine = false;
	int32 FireWallPlayer;
public:
	FPawnType toFPawnType () override;
	Null ();
	void setFirewall ( const bool state );
	bool isFirewallOn () const;	
	int32 getPlayer () const override;
	void setFireWallPlayer ( int32 player, bool Me);
	bool isMoveable () const override;
	~Null () override;
};

UCLASS()
class RAYNETAB_TEST13_API UChessBoard :public UObject{
	GENERATED_BODY ()
	// left down cornor is 0,0 up right is 7,7
	Board chessBoard;

	int32 player1;
	int32 player2;
	
	bool MovePointServer = false;
public:
	UChessBoard();
	void SetPawn_1 ( TArray<ShowType> Setting );
	void SetPawn_2 ( TArray<ShowType> Setting );
	bool getMovePointServer ();
	void clearMovePoint ();
	void LineBoost ( int32 player, Place place, bool used );
	void FireWall ( int32 player, Place place, bool used );
	void VirusCheck ( int32 player, Place place );
	void NotFoundSwap ( int32 player, Place from, Place to );
	void NotFoundNoSwap ( int32 player, Place from, Place to );
	void ShowMoveablePoint ( Place pawn );
	void ShowMoveablePoint_Card ( int32 PlayerID, TerminalCard card, TArray<bool> _terminal );
	void Move ( Place from, Place to );
	void MoveToServer ( Place from);
	TArray<FPawnType> Refresh ();
};