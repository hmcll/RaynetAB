// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "ChessBoard.h"


UChessBoard::UChessBoard() {
	//Initalize
	for( int i = 0; i < 8; i++ ) {
		chessBoard.AddZeroed();
		for( int j = 0; j < 8; j++ ) {
			chessBoard[i].Add(TSharedPtr<Null>(new Null()));
		}
	}
	player1 = MakeShareable(new FChessboardPlayer());
	player2 = MakeShareable(new FChessboardPlayer());
	player1->_enemy = player2;
	player2->_enemy = player1;
	player1->playerid = 1;
	player2->playerid = 2;
}

/*
To initalize MyPawn
@Param
@Pattern Right to Left 1 = Virus 0 = Link
*/
void UChessBoard::SetPawn_1(TArray<ShowType> Setting) {
	TArray<int32> Y;
	Y.Init(0, 8);
	Y[3] = 1;
	Y[4] = 1;
	for( int i = 0; i < 8; i++ ) {

		if( Setting[i] == ShowType::Virus )
			chessBoard[i][Y[i]] = TSharedPtr<Virus>(new Virus(player1));
		else
			chessBoard[i][Y[i]] = TSharedPtr<Link>(new Link(player1));
	}
}
/*
To initalize EnemyPawn
@Param
@Pattern Right to Left 1 = Virus 0 = Link
*/
void UChessBoard::SetPawn_2(TArray<ShowType> Setting) {
	TArray<int32> Y;
	Y.Init(7, 8);
	Y[3] = 6;
	Y[4] = 6;
	for( int i = 0; i < 8; i++ ) {
		if( Setting[i] == ShowType::Virus )
			chessBoard[7 - i][Y[i]] = TSharedPtr<Virus>(new Virus(player2));
		else
			chessBoard[7 - i][Y[i]] = TSharedPtr<Link>(new Link(player2));
	}
}

void UChessBoard::LineBoost(Place place) {
	auto thisplayer = chessBoard[place.X][place.Y].Get()->getPlayer();

	auto MoveablePlace = StaticCastSharedPtr<Moveable>(chessBoard[place.X][place.Y]);
	if( thisplayer->_terminal[(int32) TerminalCard::LineBoost] ) {
		MoveablePlace->setLineBoost(false);
	}
	else {
		MoveablePlace->setLineBoost(true);
	}
	thisplayer->_terminal[(int32) TerminalCard::LineBoost] = !thisplayer->_terminal[(int32) TerminalCard::LineBoost];
}
void UChessBoard::FireWall(int32 player, Place place) {
	auto thisplayer = player2;
	if( player == 1 )
		thisplayer = player1;

	auto NullPlace = StaticCastSharedPtr<Null>(chessBoard[place.X][place.Y]);
	if( thisplayer->_terminal[(int32) TerminalCard::Firewall] ) {
		NullPlace->setFirewall(false);
	}
	else {
		NullPlace->setFirewall(true);
		NullPlace->setFireWallPlayer(thisplayer, thisplayer == player1);
	}
	thisplayer->_terminal[(int32) TerminalCard::Firewall] = !thisplayer->_terminal[(int32) TerminalCard::Firewall];
}
void UChessBoard::VirusCheck(int32 player, Place place) {
	auto thisplayer = player2;
	if( player == 1 )
		thisplayer = player1;
	( (Moveable*) ( chessBoard[place.X][place.Y].Get() ) )->setShowingOff(true);
	thisplayer->_terminal[(int32) TerminalCard::VirusCheck] = !TERMINALCARD_USED;
}
void UChessBoard::NotFoundSwap(int32 player, Place from, Place to) {
	auto thisplayer = player2;
	if( player == 1 )
		thisplayer = player1;
	auto Mofrom = ( (Moveable*) chessBoard[from.X][from.Y].Get() );
	auto Moto = ( (Moveable*) chessBoard[to.X][to.Y].Get() );
	{
		bool temp = Mofrom->isLineBoosting();
		Mofrom->setLineBoost(Moto->isLineBoosting());
		Moto->setLineBoost(temp);
	}
	Mofrom->setShowingOff(false);
	Moto->setShowingOff(false);
	Swap<TSharedPtr<Pawn>>(chessBoard[from.X][from.Y], chessBoard[to.X][to.Y]);
	thisplayer->_terminal[(int32) TerminalCard::NotFound] = TERMINALCARD_USED;

}
void UChessBoard::NotFoundNoSwap(int32 player, Place from, Place to) {
	auto thisplayer = player2;
	if( player == 1 )
		thisplayer = player1;

	( (Moveable*) chessBoard[from.X][from.Y].Get() )->setShowingOff(false);
	( (Moveable*) chessBoard[to.X][to.Y].Get() )->setShowingOff(false);

	thisplayer->_terminal[(int32) TerminalCard::NotFound] = TERMINALCARD_USED;
}

void UChessBoard::ShowMoveablePoint(Place pawn) {
	auto thisplayer = chessBoard[pawn.X][pawn.Y].Get()->getPlayer();
	TArray<Place> points;
	if( chessBoard[pawn.X][pawn.Y]->getType() != ShowType::Null )
		if( ( (Moveable*) ( chessBoard[pawn.X][pawn.Y].Get() ) )->isLineBoosting() ) {
			TArray<int32> joints;
			joints.Init(0, 4);
			enum direction {
				up = 0, down = 1, right = 2, left = 3
			};
			if( pawn.X < 7 )
				joints[right] = ( !chessBoard[pawn.X + 1][pawn.Y]->isMoveable() );
			if( pawn.X > 0 )
				joints[left] = ( !chessBoard[pawn.X - 1][pawn.Y]->isMoveable() );
			if( pawn.Y < 7 )
				joints[up] = ( !chessBoard[pawn.X][pawn.Y + 1]->isMoveable() );
			if( pawn.Y > 0 )
				joints[down] = ( !chessBoard[pawn.X][pawn.Y - 1]->isMoveable() );


			if( pawn.X < 6 && joints[right] )
				points.Add({pawn.X + 2, pawn.Y});
			if( pawn.X > 1 && joints[left] )
				points.Add({pawn.X - 2, pawn.Y});
			if( pawn.Y < 6 && joints[up] )
				points.Add({pawn.X, pawn.Y + 2});
			if( pawn.Y > 1 && joints[down] )
				points.Add({pawn.X, pawn.Y - 2});


			if( pawn.X < 7 && pawn.Y < 7 && ( joints[up] || joints[right] ) )
				points.Add({pawn.X + 1, pawn.Y + 1});
			if( pawn.X < 7 && pawn.Y > 0 && ( joints[down] || joints[right] ) )
				points.Add({pawn.X + 1, pawn.Y - 1});
			if( pawn.X > 0 && pawn.Y < 7 && ( joints[up] || joints[left] ) )
				points.Add({pawn.X - 1, pawn.Y + 1});
			if( pawn.X > 0 && pawn.Y > 0 && ( joints[down] || joints[left] ) )
				points.Add({pawn.X - 1, pawn.Y - 1});
			if( thisplayer == player1 ) {
				if( pawn.Y == 7 ) {
					if( pawn.X == 2 && joints[right] )
						points.Add({-1,-1});
					if( pawn.X == 5 && joints[left] )
						points.Add({-1,-1});
					if( pawn.X == 3 || pawn.X == 4 )
						points.Add({-1,-1});
				}
				else if( pawn.Y == 6 ) {
					if( joints[up] && ( pawn.X == 3 || pawn.X == 4 ) )
						points.Add({-1,-1});
				}
			}
			else {
				if( pawn.Y == 0 ) {
					if( pawn.X == 2 && joints[right] )
						points.Add({-1,-1});
					if( pawn.X == 5 && joints[left] )
						points.Add({-1,-1});
					if( pawn.X == 3 || pawn.X == 4 )
						points.Add({-1,-1});
				}
				else if( pawn.Y == 1 ) {
					if( joints[down] && ( pawn.X == 3 || pawn.X == 4 ) )
						points.Add({-1,-1});
				}

			}
		}
		else {
			if( pawn.X < 7 )
				points.Add({pawn.X + 1, pawn.Y});
			if( pawn.X > 0 )
				points.Add({pawn.X - 1, pawn.Y});
			if( pawn.Y < 7 )
				points.Add({pawn.X, pawn.Y + 1});
			if( pawn.Y > 0 )
				points.Add({pawn.X, pawn.Y - 1});
			if( pawn.Y == ( thisplayer == player1 ? 7 : 0 ) && ( pawn.X == 3 || pawn.X == 4 ) )
				points.Add({-1,-1});
		}
		for( int32 i = 0; i < points.Num(); i++ ) {
			if( points[i] == Place(-1, -1) )continue;
			if( chessBoard[points[i].X][points[i].Y]->isMoveable() ) {
				if( thisplayer == chessBoard[points[i].X][points[i].Y]->getPlayer() ) {
					points.RemoveAt(i--);
					continue;
				}
			}
			else {
				if( ( (Null*) chessBoard[points[i].X][points[i].Y].Get() )->isFirewallOn() ) {
					points.RemoveAt(i--);
				}
			}
		}
		for( int32 i = 0; i < points.Num(); i++ ) {
			if( points[i] == Place(-1, -1) ) {
				MovePointServer = true;
				continue;
			}
			chessBoard[points[i].X][points[i].Y]->setMovePoint(true);
		}
}
bool UChessBoard::getMovePointServer() {
	return MovePointServer;
}

void UChessBoard::Move(Place from, Place to) {
	if( chessBoard[to.X][to.Y]->isMoveable() ) {
		chessBoard[from.X][from.Y]->getPlayer()->addToDataBase(StaticCastSharedPtr<Moveable>(chessBoard[to.X][to.Y])->isLineBoosting(), chessBoard[to.X][to.Y]->getType());
		chessBoard[to.X][to.Y].Reset();
		chessBoard[to.X][to.Y] = TSharedPtr<Null>(new Null());
		Swap<TSharedPtr<Pawn>>(chessBoard[from.X][from.Y], chessBoard[to.X][to.Y]);
	}
	else {
		Swap<TSharedPtr<Pawn>>(chessBoard[from.X][from.Y], chessBoard[to.X][to.Y]);
	}
}
void UChessBoard::MoveToServer(Place from) {
	chessBoard[from.X][from.Y]->getPlayer()->_enemy->addToServer(StaticCastSharedPtr<Moveable>(chessBoard[from.X][from.Y])->isShowingOff(), StaticCastSharedPtr<Moveable>(chessBoard[from.X][from.Y])->isLineBoosting(), chessBoard[from.X][from.Y]->getType());
	chessBoard[from.X][from.Y].Reset();
	chessBoard[from.X][from.Y] = TSharedPtr<Null>(new Null());
}
TArray<FPawnType> UChessBoard::Refresh(int32 playerid) {
	TArray <FPawnType> EnumBoard;
	for( int i = 0; i < 8; i++ ) {
		for( int j = 0; j < 8; j++ ) {
			EnumBoard.Add(chessBoard[j][i]->toFPawnType(playerid));
		}
	}

	return EnumBoard;
}
Link::Link(TSharedPtr<FChessboardPlayer> player) {
	_player = player;
	_type = ShowType::Link;
}
Link::~Link() {
}
Pawn::~Pawn() {
}
ShowType Pawn::getType() const {
	return _type;
}
TSharedPtr<FChessboardPlayer> Pawn::getPlayer() const {
	return _player;
}
void Pawn::setMovePoint(const bool state) {
	_IsMovePoint = state;
}
bool Pawn::isMovePoint() const {
	return _IsMovePoint;
}
Null::Null() {
	_player = nullptr;
	_type = ShowType::Null;
}
void Null::setFirewall(const  bool state) {
	_IsFireWallOn = state;
}
bool Null::isFirewallOn() const {
	return _IsFireWallOn;
}
TSharedPtr<FChessboardPlayer> Null::getPlayer() const {
	if( _IsFireWallOn ) return FireWallPlayer;
	return nullptr;
}
Null::~Null() {
}
Virus::Virus(TSharedPtr<FChessboardPlayer>  player) {
	_player = player;
	_type = ShowType::Virus;
}
Virus::~Virus() {
}
bool Moveable::isMoveable() const {
	return true;
}
bool Moveable::isLineBoosting() const {
	return _IsLineBoosting;
}
void Moveable::setLineBoost(const bool state) {
	_IsLineBoosting = state;
}
bool Moveable::isShowingOff() const {
	return _IsShowingOff;
}
void Moveable::setShowingOff(const bool state) {
	_IsShowingOff = state;
}
bool Moveable::isSelected() const {
	return _IsSelected;
}
void Moveable::setSelected(const bool state) {
	_IsSelected = false;
}
bool Null::isMoveable() const {
	return false;
}
FPawnType Null::toFPawnType(int32 playerid) {
	FPawnType ret;
	ret._IsMovePoint = _IsMovePoint;
	ret._Type = _IsFireWallOn ? ShowType::FireWall: ShowType::Null;
	return ret;
}
FPawnType Virus::toFPawnType(int32 playerid) {
	FPawnType ret;
	if( _player->playerid == playerid )
		ret._Type = ShowType::Virus;
	else
		if( _IsShowingOff )
			ret._Type = ShowType::Virus;
	
	ret._IsMovePoint = _IsMovePoint;
	ret._IsShowingOff = _IsShowingOff;
	ret._IsLineBoosting = _IsLineBoosting;
	return ret;
}
FPawnType Link::toFPawnType(int32 playerid) {
	FPawnType ret;
	if( _player->playerid == 1 )
		ret._Type = ShowType::Link;
	else 
		if(_IsShowingOff)
			ret._Type = ShowType::Link;
	ret._IsMovePoint = _IsMovePoint;
	ret._IsShowingOff = _IsShowingOff;
	ret._IsLineBoosting = _IsLineBoosting;
	return ret;
}
void UChessBoard::clearMovePoint() {
	MovePointServer = false;
	for( int i = 0; i < 8; i++ ) {
		for( int j = 0; j < 8; j++ ) {
			chessBoard[i][j]->setMovePoint(false);
		}
	}
}
void UChessBoard::ShowMoveablePoint_Card(int32 PlayerID, TerminalCard card) {
	int32 player = PlayerID;
	auto _terminal = PlayerID == 1 ? player1->_terminal : player2->_terminal;
	switch( card ) {
	case TerminalCard::LineBoost:
		if( _terminal[(int32) TerminalCard::LineBoost] == TERMINALCARD_USED ) {
			for( int i = 0; i < 8; i++ ) {
				for( int j = 0; j < 8; j++ ) {
					if( ( (Moveable*) chessBoard[i][j].Get() )->isLineBoosting() && chessBoard[i][j]->getPlayer()->playerid == PlayerID ) {
						chessBoard[i][j]->setMovePoint(true);
						return;
					}
				}
			}
		}
		else {
			for( int i = 0; i < 8; i++ ) {
				for( int j = 0; j < 8; j++ ) {
					if( chessBoard[i][j]->isMoveable() && chessBoard[i][j]->getPlayer()->playerid == PlayerID ) {
						chessBoard[i][j]->setMovePoint(true);
					}
				}
			}
		}
		break;
	case TerminalCard::Firewall:
		if( _terminal[(int32) TerminalCard::Firewall] == TERMINALCARD_USED ) {
			for( int i = 0; i < 8; i++ ) {
				for( int j = 0; j < 8; j++ ) {
					if( !chessBoard[i][j]->isMoveable() )
						if( ( (Null*) chessBoard[i][j].Get() )->isFirewallOn() )
							if( chessBoard[i][j]->getPlayer()->playerid == PlayerID ) {
								chessBoard[i][j]->setMovePoint(true);
								return;
							}
				}
			}
		}
		else {
			for( int i = 0; i < 8; i++ ) {
				for( int j = 1; j < 7; j++ ) {
					if( ( j == 1 || j == 6 ) && ( i == 3 || i == 4 ) )continue;
					if( !chessBoard[i][j]->isMoveable() )
						if( !( (Null*) chessBoard[i][j].Get() )->isFirewallOn() ) {
							chessBoard[i][j]->setMovePoint(true);
						}
				}
			}
		}
		break;
	case TerminalCard::VirusCheck:
		for( int i = 0; i < 8; i++ ) {
			for( int j = 0; j < 8; j++ ) {
				if( chessBoard[i][j]->isMoveable() && chessBoard[i][j]->getPlayer()->playerid != PlayerID ) {
					chessBoard[i][j]->setMovePoint(true);
				}
			}
		}
		break;
	case TerminalCard::NotFound:
		for( int i = 0; i < 8; i++ ) {
			for( int j = 0; j < 8; j++ ) {
				if( chessBoard[i][j]->isMoveable() && chessBoard[i][j]->getPlayer()->playerid == PlayerID ) {
					chessBoard[i][j]->setMovePoint(true);
				}
			}
		}
		break;
	default:
		break;
	}

}
void Null::setFireWallPlayer(TSharedPtr<FChessboardPlayer> player, bool Me) {
	FireWallPlayer = player;
	_IsMine = Me;
}

FChessboardPlayer::FChessboardPlayer() {
	_terminal.Init(false, 4);
}
bool FChessboardPlayer::addToServer(bool isShowingOff, bool islineboosting, const ShowType Type) {
	switch( Type ) {
	case ShowType::Link:
		_server_L++;
		Showingoff = isShowingOff ? ServerShowingOff::Link : Showingoff;
		break;
	case ShowType::Virus:
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

bool FChessboardPlayer::addToDataBase(bool islineboosting, ShowType Type) {
	switch( Type ) {
	case ShowType::Link:
		_dataBase_L++;
		break;
	case ShowType::Virus:
		_dataBase_V++;
		break;
	default:
		return false;
		break;
	}
	if( islineboosting ) _enemy->setTerminalUse(TerminalCard::LineBoost, TERMINALCARD_UNUSED);
	return true;
}

bool FChessboardPlayer::getTerminalUse(TerminalCard card) {
	return _terminal[int(card)];
}

void FChessboardPlayer::setTerminalUse(TerminalCard card, bool state) {
	_terminal[int(card)] = state;
}

