// Fill out your copyright notice in the Description page of Project Settings.

#include "RaynetAB_Test13.h"
#include "ChessBoard.h"


ChessBoard::ChessBoard ( TWeakObjectPtr<AGamePlayer> Me, TWeakObjectPtr<AGamePlayer> Enemy ):
	_Me ( Me ),
	_Enemy ( Enemy ) {
	//Initalize
	for ( int i = 0; i < 8; i++ ) {
		chessBoard.AddZeroed ();
		for ( int j = 0; j < 8; j++ ) {
			chessBoard[i].Add ( TSharedPtr<Null> ( new Null () ) );
		}
	}
}
/*
To initalize Yellow Pawns (MyPawn)
@Param
@Pattern Right to Left 1 = Virus 0 = Link
*/
bool ChessBoard::SetPawn_Y ( int Pattern ) {
	TArray<int32> Y;
	Y.Init ( 0, 8 );
	Y[3] = 1;
	Y[4] = 1;
	for ( int i = 0; i < 8; i++ ) {

		if ( Pattern % 2 )
			chessBoard[i][Y[i]] = TSharedPtr<Virus> ( new Virus ( _Me ) );
		else
			chessBoard[i][Y[i]] = TSharedPtr<Link> ( new Link ( _Me ) );
		Pattern >>= 1;
	}
	return true;
}

/*
To initalize Blue Pawns (EnemyPawn)
@Param
@Pattern Right to Left 1 = Virus 0 = Link
*/
bool ChessBoard::SetPawn_B ( int Pattern ) {
	TArray<int32> Y;
	Y.Init ( 7, 8 );
	Y[3] = 6;
	Y[4] = 6;
	for ( int i = 0; i < 8; i++ ) {
		if ( Pattern % 2 )
			chessBoard[i][Y[i]] = TSharedPtr<Virus> ( new Virus ( _Enemy ) );
		else
			chessBoard[i][Y[i]] = TSharedPtr<Link> ( new Link ( _Enemy ) );
		Pattern >>= 1;
	}
	return true;
}

bool ChessBoard::LineBoost ( TWeakObjectPtr<AGamePlayer> player, Place place ) {
	if ( !chessBoard[place.X][place.Y]->isMoveable () )
		return false;
	auto MoveablePlace = (Moveable*) chessBoard[place.X][place.Y].Get ();
	if ( MoveablePlace->getPlayer ()->_playerID != player->_playerID )
		return false;
	if ( player->getTerminalUse ( TerminalCard::LineBoost ) == TERMINALCARD_USED ) {
		if ( !( MoveablePlace->isLineBoosting () ) ) {
			return false;
		}
		player->setTerminalUse ( TerminalCard::LineBoost, TERMINALCARD_UNUSED );
		MoveablePlace->setLineBoost ( false );
	}
	else {

		if ( ( MoveablePlace->isLineBoosting () ) ) {
			return false;
		}
		player->setTerminalUse ( TerminalCard::LineBoost, TERMINALCARD_USED );
		MoveablePlace->setLineBoost ( true );
	}
	return true;
}
bool ChessBoard::FireWall ( TWeakObjectPtr<AGamePlayer> player, Place place ) {
	if ( chessBoard[place.X][place.Y]->isMoveable () )
		return false;
	auto NullPlace = (Null*) chessBoard[place.X][place.Y].Get ();;
	if ( player->getTerminalUse ( TerminalCard::Firewall ) == TERMINALCARD_USED ) {
		if ( !NullPlace->isFirewallOn () ) {
			return false;
		}
		if ( NullPlace->getPlayer ()->_playerID != player->_playerID ) {
			return false;
		}
		player->setTerminalUse ( TerminalCard::Firewall, TERMINALCARD_UNUSED );
		NullPlace->setFirewall ( false );
	}
	else {
		if ( ( NullPlace->isFirewallOn () ) ) {
			return false;
		}
		player->setTerminalUse ( TerminalCard::Firewall, TERMINALCARD_USED );
		NullPlace->setFirewall ( true );
	}
	return true;
}
bool ChessBoard::VirusCheck ( TWeakObjectPtr<AGamePlayer> player, Place place ) {
	if ( player->getTerminalUse ( TerminalCard::VirusCheck ) == TERMINALCARD_USED )
		return false;
	if ( !chessBoard[place.X][place.Y]->isMoveable () )
		return false;
	if ( player->_playerID == chessBoard[place.X][place.Y]->getPlayer ()->_playerID )
		return false;
	player->setTerminalUse ( TerminalCard::VirusCheck, true );
	( (Moveable*) ( chessBoard[place.X][place.Y].Get () ) )->setShowingOff ( true );
	return true;
}
bool ChessBoard::NotFoundSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to ) {
	if ( player->getTerminalUse ( TerminalCard::VirusCheck ) == TERMINALCARD_USED )
		return false;
	if ( !chessBoard[from.X][from.Y]->isMoveable () || !chessBoard[to.X][to.Y]->isMoveable () )
		return false;
	if ( player->_playerID != chessBoard[from.X][from.Y]->getPlayer ()->_playerID )
		return false;
	if ( player->_playerID != chessBoard[to.X][to.Y]->getPlayer ()->_playerID )
		return false;
	auto Mofrom = ( (Moveable*) chessBoard[from.X][from.Y].Get () );
	auto Moto = ( (Moveable*) chessBoard[to.X][to.Y].Get () );
	{
		bool temp = Mofrom->isLineBoosting ();
		Mofrom->setLineBoost ( Moto->isLineBoosting () );
		Moto->setLineBoost ( temp );
	}
	Mofrom->setShowingOff ( false );
	Moto->setShowingOff ( false );
	//Swap<TSharedPtr<Pawn>> ( chessBoard[from.X][from.Y], chessBoard[to.X][to.Y] );
	return true;
}
bool ChessBoard::NotFoundNoSwap ( TWeakObjectPtr<AGamePlayer> player, Place from, Place to ) {
	if ( player->getTerminalUse ( TerminalCard::VirusCheck ) == TERMINALCARD_USED )
		return false;
	if ( !chessBoard[from.X][from.Y]->isMoveable () || !chessBoard[to.X][to.Y]->isMoveable () )
		return false;
	if ( player->_playerID != chessBoard[from.X][from.Y]->getPlayer ()->_playerID )
		return false;
	if ( player->_playerID != chessBoard[to.X][to.Y]->getPlayer ()->_playerID )
		return false;
	( (Moveable*) chessBoard[from.X][from.Y].Get () )->setShowingOff ( false );
	( (Moveable*) chessBoard[to.X][to.Y].Get () )->setShowingOff ( false );
	return false;
}
// Not Including the entering server part.
bool ChessBoard::ShowMoveablePoint ( Place pawn ) {
	TArray<Place> points;
	if ( chessBoard[pawn.X][pawn.Y]->getType () != PawnType::Null )
		if ( ( (Moveable*) ( chessBoard[pawn.X][pawn.Y].Get () ) )->isLineBoosting () ) {
			TArray<int32> joints;
			joints.Init ( 0, 4 );
			enum direction {
				up = 0, down = 1, right = 2, left = 3
			};
			if ( pawn.X < 7 )
				joints[right] = ( !chessBoard[pawn.X + 1][pawn.Y]->isMoveable () );
			if ( pawn.X > 0 )
				joints[left] = ( !chessBoard[pawn.X - 1][pawn.Y]->isMoveable () );
			if ( pawn.Y < 7 )
				joints[up] = ( !chessBoard[pawn.X][pawn.Y + 1]->isMoveable () );
			else if ( pawn.X == 3 || pawn.X == 4 )
				points.Add ( {-1,-1} );
			if ( pawn.Y > 0 )
				joints[down] = ( !chessBoard[pawn.X][pawn.Y - 1]->isMoveable () );

			if ( pawn.X < 6 && joints[right] )
				points.Add ( {pawn.X + 2, pawn.Y} );

			if ( pawn.X > 1 && joints[left] )
				points.Add ( {pawn.X - 2, pawn.Y} );

			if ( pawn.Y < 6 && joints[up] )
				points.Add ( {pawn.X, pawn.Y + 2} );
			else if ( pawn.X == 3 || pawn.X == 4 )
				points.Add ( {-1,-1} );

			if ( pawn.Y > 1 && joints[down] )
				points.Add ( {pawn.X, pawn.Y - 2} );

			if ( pawn.X < 7 && pawn.Y < 7 && ( joints[up] || joints[right] ) )
				points.Add ( {pawn.X + 1, pawn.Y + 1} );
			else if ( pawn.Y == 7 || ( pawn.X == 3 || pawn.X == 4 ) )
				points.Add ( Place ( -1, -1 ) );
			if ( pawn.X < 7 && pawn.Y > 0 && ( joints[up] || joints[left] ) )
				points.Add ( {pawn.X + 1, pawn.Y - 1} );
			if ( pawn.X > 0 && pawn.Y < 7 && ( joints[down] || joints[right] ) )
				points.Add ( {pawn.X - 1, pawn.Y + 1} );
			if ( pawn.X > 0 && pawn.Y > 0 && ( joints[down] || joints[left] ) )
				points.Add ( {pawn.X - 1, pawn.Y - 1} );
		}
		else {
			if ( pawn.X < 7 )
				points.Add ( {pawn.X + 1, pawn.Y} );
			if ( pawn.X > 0 )
				points.Add ( {pawn.X - 1, pawn.Y} );
			if ( pawn.Y < 7 )
				points.Add ( {pawn.X, pawn.Y + 1} );
			if ( pawn.Y > 0 )
				points.Add ( {pawn.X, pawn.Y - 1} );
		}
	else {
		return false;
	}
	for ( int32 i = 0; i < points.Num (); i++ ) {
		if ( points[i] == Place ( -1, -1 ) )continue;
		if ( chessBoard[points[i].X][points[i].Y]->isMoveable () ) {
			if ( chessBoard[pawn.X][pawn.Y]->getPlayer ().IsValid () || chessBoard[points[i].X][points[i].Y]->getPlayer ().IsValid () ) {
				points.RemoveAt ( i );
				continue;
			}
			if ( chessBoard[pawn.X][pawn.Y]->getPlayer ()->_playerID == chessBoard[points[i].X][points[i].Y]->getPlayer ()->_playerID ) {
				points.RemoveAt ( i );
				continue;
			}
		}
		else {
			if ( ( (Null*) chessBoard[points[i].X][points[i].Y].Get () )->isFirewallOn () ) {
				points.RemoveAt ( i );
			}
		}
	}
	for ( int32 i = 0; i < points.Num (); i++ ) {
		if ( points[i] == Place ( -1, -1 ) ) MovePointServer = true;
		chessBoard[points[i].X][points[i].Y]->setMovePoint ( true );
	}
	return true;
}

bool ChessBoard::getMovePointServer () {
	return MovePointServer;
}

bool ChessBoard::Move ( Place from, Place to ) {
	if ( !chessBoard[from.X][from.Y]->isMoveable () )
		return false;
	if ( chessBoard[to.X][to.Y]->isMoveable () ) {
		if ( chessBoard[from.X][from.Y]->getPlayer ().IsValid () || chessBoard[to.X][to.Y]->getPlayer ().IsValid () )
			return false;
		if ( chessBoard[from.X][from.Y]->getPlayer ()->_playerID == chessBoard[to.X][to.Y]->getPlayer ()->_playerID )
			return false;
		chessBoard[from.X][from.Y]->getPlayer ()->addToDataBase ( chessBoard[to.X][to.Y]->getType () );
		chessBoard[to.X][to.Y].Reset ();
		chessBoard[to.X][to.Y] = TSharedPtr<Null> ( new Null () );
		//Swap<TSharedPtr<Pawn>>(chessBoard[from.X][from.Y],chessBoard[to.X][to.Y]);
	}
	else {
		if ( ( (Null*) chessBoard[to.X][to.Y].Get () )->isFirewallOn () ) {
			return false;
		}
		//Swap<TSharedPtr<Pawn>> ( chessBoard[from.X][from.Y], chessBoard[to.X][to.Y] );
	}
	return true;
}

bool ChessBoard::MoveToServer ( Place from ) {
	if ( from.Y == 7 && ( from.X == 4 || from.X == 3 ) ) {
		if ( !chessBoard[from.X][from.Y]->isMoveable () )
			return false;
		chessBoard[from.X][from.Y]->getPlayer ()->getEnemy ()->addToServer ( chessBoard[from.X][from.Y]->getType () );
		chessBoard[from.X][from.Y].Reset ();
		chessBoard[from.X][from.Y] = TSharedPtr<Null> ( new Null () );
		return true;
	}
	else
		return false;
}

TArray<TArray<ShowType>> ChessBoard::Refresh () {
	TArray < TArray<ShowType>> EnumBoard;
	for ( int i = 0; i < 8; i++ ) {
		EnumBoard.AddZeroed ( 1);
		for ( int j = 0; j < 8; j++ ) {
			EnumBoard[i].Add(chessBoard[i][j]->toEnum ());
		}
	}
	return EnumBoard;
}

Link::Link ( TWeakObjectPtr<AGamePlayer> player ) {
	_player = player;
	_type = PawnType::Link;
}

Link::~Link () {
}

Pawn::~Pawn () {
}

PawnType Pawn::getType () const {
	return _type;
}


TWeakObjectPtr<AGamePlayer> Pawn::getPlayer () const {
	return _player;
}

void Pawn::setMovePoint ( const bool state ) {
	_IsMovePoint = state;
}

bool Pawn::isMovePoint () const {
	return _IsMovePoint;
}

Null::Null () {
	_player = nullptr;
	_type = PawnType::Link;
}

void Null::setFirewall ( const  bool state ) {
	_IsFireWallOn = true;
}

bool Null::isFirewallOn () const {
	return _IsFireWallOn;
}

TWeakObjectPtr<AGamePlayer> Null::getPlayer () const {
	return nullptr;
}

Null::~Null () {
}

Virus::Virus ( TWeakObjectPtr<AGamePlayer>  player ) {
	_player = player;
	_type = PawnType::Virus;
}

Virus::~Virus () {
}
bool Moveable::isMoveable () const {
	return true;
}

bool Moveable::isLineBoosting () const {
	return _IsLineBoosting;
}

void Moveable::setLineBoost ( const bool state ) {
	_IsLineBoosting = state;
}

bool Moveable::isShowingOff () const {
	return _IsShowingOff;
}

void Moveable::setShowingOff ( const bool state ) {
	_IsShowingOff = state;
}

bool Null::isMoveable () const {
	return false;
}

ShowType Null::toEnum () {
	if ( _IsMovePoint ) return ShowType::MovePioint;
	if ( _IsFireWallOn ) return ShowType::FireWall;
	return ShowType::Null;
}
ShowType Virus::toEnum () {
	if ( _player->_playerID == 0 )
		if ( _IsLineBoosting )
			if ( _IsShowingOff )
				return ShowType::VirusYLO;
			else
				return ShowType::VirusYO;
		else
			if ( _IsShowingOff )
				return ShowType::VirusYL;
			else
				return ShowType::VirusY;
	else
		if ( _IsShowingOff )
			if ( _IsLineBoosting )
				if ( _IsMovePoint )
					return ShowType::VirusBLM;
				else
					return ShowType::VirusBL;
			else
				if ( _IsMovePoint )
					return ShowType::VirusBM;
				else
					return ShowType::VirusB;
		else
			if ( _IsLineBoosting )
				if ( _IsMovePoint )
					return ShowType::BackBLM;
				else
					return ShowType::BackBL;
			else
				if ( _IsMovePoint )
					return ShowType::BackBM;
				else
					return ShowType::BackB;
}

ShowType Link::toEnum () {
	if ( _player->_playerID == 0 )
		if ( _IsLineBoosting )
			if ( _IsShowingOff )
				return ShowType::LinkYLO;
			else
				return ShowType::LinkYO;
		else
			if ( _IsShowingOff )
				return ShowType::LinkYL;
			else
				return ShowType::LinkY;
	else
		if ( _IsShowingOff )
			if ( _IsLineBoosting )
				if ( _IsMovePoint )
					return ShowType::LinkBLM;
				else
					return ShowType::LinkBL;
			else
				if ( _IsMovePoint )
					return ShowType::LinkBM;
				else
					return ShowType::LinkB;
		else
			if ( _IsLineBoosting )
				if ( _IsMovePoint )
					return ShowType::BackBLM;
				else
					return ShowType::BackBL;
			else
				if ( _IsMovePoint )
					return ShowType::BackBM;
				else
					return ShowType::BackB;
}
