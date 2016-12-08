// Fill out your copyright notice in the Description page of Project Settings.

#include "Raynet_Test14.h"
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
bool ChessBoard::SetPawn_Y ( TArray<ShowType> Setting ) {
	TArray<int32> Y;
	Y.Init ( 0, 8 );
	Y[3] = 1;
	Y[4] = 1;
	for ( int i = 0; i < 8; i++ ) {

		if ( Setting[i] == ShowType::VirusY )
			chessBoard[i][Y[i]] = TSharedPtr<Virus> ( new Virus ( _Me ) );
		else
			chessBoard[i][Y[i]] = TSharedPtr<Link> ( new Link ( _Me ) );
	}
	return true;
}

/*
To initalize Blue Pawns (EnemyPawn)
@Param
@Pattern Right to Left 1 = Virus 0 = Link
*/
bool ChessBoard::SetPawn_B ( TArray<ShowType> Setting ) {
	TArray<int32> Y;
	Y.Init ( 7, 8 );
	Y[3] = 6;
	Y[4] = 6;
	for ( int i = 0; i < 8; i++ ) {
		if ( Setting[i] == ShowType::VirusY )
			chessBoard[i][Y[i]] = TSharedPtr<Virus> ( new Virus ( _Enemy ) );
		else
			chessBoard[i][Y[i]] = TSharedPtr<Link> ( new Link ( _Enemy ) );
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
	if ( place.Y == 7 || place.Y == 0 )return false;
	if ( place.X == 4 || place.X == 3 )
		if ( place.Y == 6 || place.Y == 1 )
			return false;
	if ( chessBoard[place.X][place.Y]->isMoveable () )
		return false;
	auto NullPlace = (Null*) chessBoard[place.X][place.Y].Get ();
	if ( player->getTerminalUse ( TerminalCard::Firewall ) == TERMINALCARD_USED ) {
		if ( !NullPlace->isFirewallOn () ) {
			return false;
		}
		if ( NullPlace->getPlayer ()->_playerID != player->_playerID ) {
			return false;
		}
		NullPlace->setFirewall ( false );
		player->setTerminalUse ( TerminalCard::Firewall, TERMINALCARD_UNUSED );
	}
	else {
		if ( ( NullPlace->isFirewallOn () ) ) {
			return false;
		}
		player->setTerminalUse ( TerminalCard::Firewall, TERMINALCARD_USED );
		NullPlace->setFirewall ( true );
		NullPlace->setFireWallPlayer ( player );
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
	Swap<TSharedPtr<Pawn>> ( chessBoard[from.X][from.Y], chessBoard[to.X][to.Y] );
	player->_terminal[(int32) TerminalCard::NotFound] = TERMINALCARD_USED;
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
	player->_terminal[(int32) TerminalCard::NotFound] = TERMINALCARD_USED;
	return true;
}
// Not Including the entering server part.
bool ChessBoard::ShowMoveablePoint ( Place pawn ) {
	TArray<Place> points;
	if ( chessBoard[pawn.X][pawn.Y]->getType () != ShowType::Null )
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
			if ( pawn.Y > 0 )
				joints[down] = ( !chessBoard[pawn.X][pawn.Y - 1]->isMoveable () );


			if ( pawn.X < 6 && joints[right] )
				points.Add ( {pawn.X + 2, pawn.Y} );
			if ( pawn.X > 1 && joints[left] )
				points.Add ( {pawn.X - 2, pawn.Y} );
			if ( pawn.Y < 6 && joints[up] )
				points.Add ( {pawn.X, pawn.Y + 2} );
			if ( pawn.Y > 1 && joints[down] )
				points.Add ( {pawn.X, pawn.Y - 2} );


			if ( pawn.X < 7 && pawn.Y < 7 && ( joints[up] || joints[right] ) )
				points.Add ( {pawn.X + 1, pawn.Y + 1} );
			if ( pawn.X < 7 && pawn.Y > 0 && ( joints[down] || joints[right] ) )
				points.Add ( {pawn.X + 1, pawn.Y - 1} );
			if ( pawn.X > 0 && pawn.Y < 7 && ( joints[up] || joints[left] ) )
				points.Add ( {pawn.X - 1, pawn.Y + 1} );
			if ( pawn.X > 0 && pawn.Y > 0 && ( joints[down] || joints[left] ) )
				points.Add ( {pawn.X - 1, pawn.Y - 1} );

			if ( pawn.Y == 7 ) {
				if ( pawn.X == 2 && joints[right] )
					points.Add ( {-1,-1} );
				if ( pawn.X == 5 && joints[left] )
					points.Add ( {-1,-1} );
				if ( pawn.X == 3 || pawn.X == 4 )
					points.Add ( {-1,-1} );
			}
			else if ( pawn.Y == 6 ) {
				if ( joints[up] && ( pawn.X == 3 || pawn.X == 4 ) )
					points.Add ( {-1,-1} );
			}
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
			if ( pawn.Y == 7 && ( pawn.X == 3 || pawn.X == 4 ) )
				points.Add ( {-1,-1} );
		}
	else {
		return false;
	}
	for ( int32 i = 0; i < points.Num (); i++ ) {
		if ( points[i] == Place ( -1, -1 ) )continue;
		if ( chessBoard[points[i].X][points[i].Y]->isMoveable () ) {
			if ( !chessBoard[pawn.X][pawn.Y]->getPlayer ().IsValid () || !chessBoard[points[i].X][points[i].Y]->getPlayer ().IsValid () ) {
				points.RemoveAt ( i-- );
				continue;
			}
			if ( chessBoard[pawn.X][pawn.Y]->getPlayer ()->_playerID == chessBoard[points[i].X][points[i].Y]->getPlayer ()->_playerID ) {
				points.RemoveAt ( i-- );
				continue;
			}
		}
		else {
			if ( ( (Null*) chessBoard[points[i].X][points[i].Y].Get () )->isFirewallOn () ) {
				points.RemoveAt ( i-- );
			}
		}
	}
	bool movetoServer = false;
	for ( int32 i = 0; i < points.Num (); i++ ) {
		if ( points[i] == Place ( -1, -1 ) ) {
			movetoServer = true;
			continue;
		}
		chessBoard[points[i].X][points[i].Y]->setMovePoint ( true );
	}
	MovePointServer = movetoServer;
	return true;
}

bool ChessBoard::getMovePointServer () {
	return MovePointServer;
}

bool ChessBoard::Move ( Place from, Place to ) {
	if ( !chessBoard[from.X][from.Y]->isMoveable () )
		return false;
	if ( chessBoard[to.X][to.Y]->isMoveable () ) {
		if ( !chessBoard[from.X][from.Y]->getPlayer ().IsValid () || !chessBoard[to.X][to.Y]->getPlayer ().IsValid () )
			return false;
		if ( chessBoard[from.X][from.Y]->getPlayer ()->_playerID == chessBoard[to.X][to.Y]->getPlayer ()->_playerID )
			return false;
		if ( !chessBoard[from.X][from.Y]->getPlayer ()->addToDataBase (chessBoard[to.X][to.Y]->toFPawnType ()._IsLineBoosting, chessBoard[to.X][to.Y]->getType () ) )return false;
		chessBoard[to.X][to.Y].Reset ();
		chessBoard[to.X][to.Y] = TSharedPtr<Null> ( new Null () );
		Swap<TSharedPtr<Pawn>> ( chessBoard[from.X][from.Y], chessBoard[to.X][to.Y] );
	}
	else {
		if ( ( (Null*) chessBoard[to.X][to.Y].Get () )->isFirewallOn () ) {
			return false;
		}
		Swap<TSharedPtr<Pawn>> ( chessBoard[from.X][from.Y], chessBoard[to.X][to.Y] );
	}
	return true;
}

bool ChessBoard::MoveToServer ( Place from ) {
	if ( !chessBoard[from.X][from.Y]->isMoveable () )
		return false;
	if ( !chessBoard[from.X][from.Y]->getPlayer ()->getEnemy ()->addToServer ( ( (Moveable*) ( chessBoard[from.X][from.Y].Get () ) )->isShowingOff (), chessBoard[from.X][from.Y]->toFPawnType ()._IsLineBoosting, chessBoard[from.X][from.Y]->getType () ) )return false;
	chessBoard[from.X][from.Y].Reset ();
	chessBoard[from.X][from.Y] = TSharedPtr<Null> ( new Null () );
	return true;
}

TArray<FPawnType> ChessBoard::Refresh () {
	TArray <FPawnType> EnumBoard;
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			EnumBoard.Add ( chessBoard[j][i]->toFPawnType () );
		}
	}
	return EnumBoard;
}

Link::Link ( TWeakObjectPtr<AGamePlayer> player ) {
	_player = player;

	_type = player->_playerID == 0 ? ShowType::LinkY : ShowType::LinkB;
}

Link::~Link () {
}

Pawn::~Pawn () {
}

ShowType Pawn::getType () const {
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
	_type = ShowType::Null;
}

void Null::setFirewall ( const  bool state ) {
	_IsFireWallOn = state;
}

bool Null::isFirewallOn () const {
	return _IsFireWallOn;
}

TWeakObjectPtr<AGamePlayer> Null::getPlayer () const {
	if ( _IsFireWallOn ) return FireWallPlayer;
	return nullptr;
}

Null::~Null () {
}

Virus::Virus ( TWeakObjectPtr<AGamePlayer>  player ) {
	_player = player;
	_type = player->_playerID == 0 ? ShowType::VirusY : ShowType::VirusB;
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

bool Moveable::isSelected () const {
	return _IsSelected;
}
void Moveable::setSelected ( const bool state ) {
	_IsSelected = false;
}

bool Null::isMoveable () const {
	return false;
}

FPawnType Null::toFPawnType () {
	FPawnType ret;
	ret._IsMovePoint = _IsMovePoint;
	ret._Type = _IsFireWallOn ? ShowType::FireWall : ShowType::Null;
	return ret;
}
FPawnType Virus::toFPawnType () {
	FPawnType ret;
	if ( _player->_playerID == 0 )
			ret._Type = ShowType::VirusY;
	else
		if ( _IsShowingOff )
				ret._Type = ShowType::VirusB;
		else
				ret._Type = ShowType::BackB;
	ret._IsMovePoint = _IsMovePoint;
	ret._IsShowingOff = _IsShowingOff;
	ret._IsLineBoosting = _IsLineBoosting;
	return ret;
}

FPawnType Link::toFPawnType () {
	FPawnType ret;
	if ( _player->_playerID == 0 )
			ret._Type = ShowType::LinkY;
	else
		if ( _IsShowingOff )
				ret._Type = ShowType::LinkB;
		else
				ret._Type = ShowType::BackB;
	ret._IsMovePoint = _IsMovePoint;
	ret._IsShowingOff = _IsShowingOff;
	ret._IsLineBoosting = _IsLineBoosting;
	return ret;
}

void ChessBoard::clearMovePoint () {
	MovePointServer = false;
	for ( int i = 0; i < 8; i++ ) {
		for ( int j = 0; j < 8; j++ ) {
			chessBoard[i][j]->setMovePoint ( false );
		}
	}
}

void ChessBoard::ShowMoveablePoint_Card ( int32 PlayerID, TerminalCard card ) {
	TWeakObjectPtr<AGamePlayer> player = PlayerID == 0 ? _Me : _Enemy;
	switch ( card ) {
	case TerminalCard::LineBoost:
		if ( player->_terminal[(int32) TerminalCard::LineBoost] == TERMINALCARD_USED ) {
			for ( int i = 0; i < 8; i++ ) {
				for ( int j = 0; j < 8; j++ ) {
					if ( ( (Moveable*) chessBoard[i][j].Get () )->isLineBoosting () && chessBoard[i][j]->getPlayer()->_playerID == PlayerID){
						chessBoard[i][j]->setMovePoint ( true );
						return;
					}
				}
			}
		}
		else {
			for ( int i = 0; i < 8; i++ ) {
				for ( int j = 0; j < 8; j++ ) {
					if ( chessBoard[i][j]->isMoveable () && chessBoard[i][j]->getPlayer ()->_playerID == PlayerID ) {
						chessBoard[i][j]->setMovePoint ( true );
					}
				}
			}
		}
		break;
	case TerminalCard::Firewall:
		if ( player->_terminal[(int32) TerminalCard::Firewall] == TERMINALCARD_USED ) {
			for ( int i = 0; i < 8; i++ ) {
				for ( int j = 0; j < 8; j++ ) {
					if(!chessBoard[i][j]->isMoveable() )
						if ( ( (Null*) chessBoard[i][j].Get () )->isFirewallOn())
							if(chessBoard[i][j]->getPlayer ()->_playerID == PlayerID ) {
								chessBoard[i][j]->setMovePoint ( true );
								return;
							}
				}
			}
		}
		else {
			for ( int i = 0; i < 8; i++ ) {
				for ( int j = 1; j < 7; j++ ) {
					if ( ( j == 1 || j == 6 ) && ( i == 3 || i == 4 ) )continue;
					if ( !chessBoard[i][j]->isMoveable () )
						if ( !( (Null*) chessBoard[i][j].Get () )->isFirewallOn () ){
						chessBoard[i][j]->setMovePoint ( true );
					}
				}
			}
		}
		break;
	case TerminalCard::VirusCheck:
		if ( !player->_terminal[(int32) TerminalCard::VirusCheck] == TERMINALCARD_USED ) {
			for ( int i = 0; i < 8; i++ ) {
				for ( int j = 0; j < 8; j++ ) {
					if ( chessBoard[i][j]->isMoveable () && chessBoard[i][j]->getPlayer ()->_playerID != PlayerID ) {
						chessBoard[i][j]->setMovePoint ( true );
					}
				}
			}
		}
		break;
	case TerminalCard::NotFound:
		if ( !player->_terminal[(int32) TerminalCard::VirusCheck] == TERMINALCARD_USED ) {
			for ( int i = 0; i < 8; i++ ) {
				for ( int j = 0; j < 8; j++ ) {
					if ( chessBoard[i][j]->isMoveable () && chessBoard[i][j]->getPlayer ()->_playerID == PlayerID ) {
						chessBoard[i][j]->setMovePoint ( true );
					}
				}
			}
		}
		break;
	default:
		break;
	}

}
bool Null::setFireWallPlayer ( TWeakObjectPtr<AGamePlayer> player) {
	if ( !_IsFireWallOn )
		return false;
	FireWallPlayer = player;
	return true;
}