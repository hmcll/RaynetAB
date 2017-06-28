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

UENUM(BlueprintType)
enum class State:uint8 {
	OnLine, Server, DataBase
};
USTRUCT(BlueprintType)
struct FChessboardPlayer {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, Category = "Variable")
		int32 _server_V = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Variable")
		int32 _server_L = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Variable")
		int32 _dataBase_V = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Variable")
		int32 _dataBase_L = 0;

	int32 playerid;
	UPROPERTY(BlueprintReadWrite, Category = "Variable")
		TArray<bool>_terminal;
	
	TSharedPtr<FChessboardPlayer> _enemy;

	UPROPERTY(BlueprintReadWrite, Category = "Variable")
		ServerShowingOff Showingoff = ServerShowingOff::Null;

	FChessboardPlayer();

	bool addToServer(bool isShowingOff, bool islineboosting, ShowType Type);

	bool addToDataBase(bool islineboosting, ShowType Type);

	bool getTerminalUse(TerminalCard card);

	void setTerminalUse(TerminalCard card, bool state);

};

class Pawn {
protected:
	TSharedPtr<FChessboardPlayer> _player;
	ShowType _type;
	bool _IsMovePoint = false;
public:
	virtual FPawnType toFPawnType(int32 playerid) = 0;
	virtual ~Pawn();
	//is able to move
	void setMovePoint(const bool state);
	bool isMovePoint() const;
	virtual bool isMoveable() const = 0;
	ShowType getType() const;
	virtual	TSharedPtr<FChessboardPlayer> getPlayer() const;
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
	bool isMoveable() const override;
	bool isLineBoosting() const;
	void setLineBoost(const bool state);
	bool isShowingOff() const;
	void setShowingOff(const bool state);
	bool isSelected() const;
	void setSelected(const bool state);
};

class Link: public Moveable {
public:
	FPawnType toFPawnType(int32 playerid) override;
	Link(TSharedPtr<FChessboardPlayer> player);
	~Link() override;
};

class Virus: public Moveable {
public:
	FPawnType toFPawnType(int32 playerid) override;
	Virus(TSharedPtr<FChessboardPlayer>  player);
	~Virus() override;
};

/*
Empty Place or Firewall
*/

class Null: public Pawn {
private:
	bool _IsFireWallOn = false;
	bool _IsMine = false;
	TSharedPtr<FChessboardPlayer> FireWallPlayer;
public:
	FPawnType toFPawnType(int32 playerid) override;
	Null();
	void setFirewall(const bool state);
	bool isFirewallOn() const;
	TSharedPtr<FChessboardPlayer> getPlayer() const override;
	void setFireWallPlayer(TSharedPtr<FChessboardPlayer> FChessboardPlayer, bool Me);
	bool isMoveable() const override;
	~Null() override;
};

UCLASS()
class RAYNETAB_TEST13_API UChessBoard:public UObject {
	GENERATED_BODY()
		// left down cornor is 0,0 up right is 7,7
		Board chessBoard;

	bool MovePointServer = false;
public:

	TSharedPtr<FChessboardPlayer> player1;
	TSharedPtr<FChessboardPlayer> player2;

	UChessBoard();
	void SetPawn_1(TArray<ShowType> Setting);
	void SetPawn_2(TArray<ShowType> Setting);
	bool getMovePointServer();
	void clearMovePoint();
	void LineBoost(Place place);
	void FireWall(int32 player, Place place);
	void VirusCheck(int32 player, Place place);
	void NotFoundSwap(int32 player, Place from, Place to);
	void NotFoundNoSwap(int32 player, Place from, Place to);
	void ShowMoveablePoint(Place pawn);
	void ShowMoveablePoint_Card(int32 PlayerID, TerminalCard card);
	void Move(Place from, Place to);
	void MoveToServer(Place from);
	TArray<FPawnType> Refresh(int32 playerid);
};