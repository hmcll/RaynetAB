// Copyright(C) 2015 - 2016  Raynet AB Development Team

#include "RaynetAB_Test13.h"
#include "C_GameInstance.h"




void UC_GameInstance::OnCreateSessionComplete ( FName SessionName, bool bWasSuccessful ) {
	GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, FString::Printf ( TEXT ( "OnCreateSessionComplete %s, %d" ), *SessionName.ToString (), bWasSuccessful ) );

	// Get the OnlineSubsystem so we can get the Session Interface
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get ();
	if ( OnlineSub ) {
		// Get the Session Interface to call the StartSession function
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();

		if ( Sessions.IsValid () ) {
			// Clear the SessionComplete delegate handle, since we finished this call
			Sessions->ClearOnCreateSessionCompleteDelegate_Handle ( _createSessionCompleteDelegateHandle );
			if ( bWasSuccessful ) {
				// Set the StartSession delegate handle
				_startSessionCompleteDelegateHandle = Sessions->AddOnStartSessionCompleteDelegate_Handle ( _startSessionCompleteDelegate );

				// Our StartSessionComplete delegate should get called after this
				Sessions->StartSession ( SessionName );
			}
		}

	}
}

void UC_GameInstance::OnStartOnlineGameComplete ( FName SessionName, bool bWasSuccessful ) {
	GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, FString::Printf ( TEXT ( "OnStartSessionComplete %s, %d" ), *SessionName.ToString (), bWasSuccessful ) );

	// Get the Online Subsystem so we can get the Session Interface
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get ();
	if ( OnlineSub ) {
		// Get the Session Interface to clear the Delegate
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();
		if ( Sessions.IsValid () ) {
			// Clear the delegate, since we are done with this call
			Sessions->ClearOnStartSessionCompleteDelegate_Handle ( _startSessionCompleteDelegateHandle );
		}
	}

	// If the start was successful, we can open a NewMap if we want. Make sure to use "listen" as a parameter!
	if ( bWasSuccessful ) {
		startedAsServer ();
	}
}

void UC_GameInstance::OnFindSessionsComplete ( bool bWasSuccessful ) {
	GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, FString::Printf ( TEXT ( "OFindSessionsComplete bSuccess: %d" ), bWasSuccessful ) );

	// Get OnlineSubsystem we want to work with
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get ();
	if ( OnlineSub ) {
		// Get SessionInterface of the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();
		if ( Sessions.IsValid () ) {
			// Clear the Delegate handle, since we finished this call
			Sessions->ClearOnFindSessionsCompleteDelegate_Handle ( _findSessionsCompleteDelegateHandle );

			// Just debugging the Number of Search results. Can be displayed in UMG or something later on
			GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, FString::Printf ( TEXT ( "Num Search Results: %d" ), SessionSearch->SearchResults.Num () ) );

			// If we have found at least 1 session, we just going to debug them. You could add them to a list of UMG Widgets, like it is done in the BP version!
			if ( SessionSearch->SearchResults.Num () > 0 ) {
				// "SessionSearch->SearchResults" is an Array that contains all the information. You can access the Session in this and get a lot of information.
				// This can be customized later on with your own classes to add more information that can be set and displayed
				for ( int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num (); SearchIdx++ ) {
					// OwningUserName is just the SessionName for now. I guess you can create your own Host Settings class and GameSession Class and add a proper GameServer Name here.
					// This is something you can't do in Blueprint for example!
					GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, FString::Printf ( TEXT ( "Session Number: %d | Sessionname: %s " ), SearchIdx + 1, *( SessionSearch->SearchResults[SearchIdx].Session.OwningUserName ) ) );
				}
			}
		}
	}
}

void UC_GameInstance::OnJoinSessionComplete ( FName SessionName, EOnJoinSessionCompleteResult::Type Result ) {
	GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, FString::Printf ( TEXT ( "OnJoinSessionComplete %s, %d" ), *SessionName.ToString (), static_cast<int32>( Result ) ) );

	// Get the OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get ();
	if ( OnlineSub ) {
		// Get SessionInterface from the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();

		if ( Sessions.IsValid () ) {
			// Clear the Delegate again
			Sessions->ClearOnJoinSessionCompleteDelegate_Handle ( _joinSessionCompleteDelegateHandle );

			// Get the first local PlayerController, so we can call "ClientTravel" to get to the Server Map
			// This is something the Blueprint Node "Join Session" does automatically!
			APlayerController * const PlayerController = GetFirstLocalPlayerController ();

			// We need a FString to use ClientTravel and we can let the SessionInterface contruct such a
			// String for us by giving him the SessionName and an empty String. We want to do this, because
			// Every OnlineSubsystem uses different TravelURLs
			FString TravelURL;

			if ( PlayerController && Sessions->GetResolvedConnectString ( SessionName, TravelURL ) ) {
				// Finally call the ClienTravel. If you want, you could print the TravelURL to see
				// how it really looks like
				PlayerController->ClientTravel ( TravelURL, ETravelType::TRAVEL_Absolute );
			}
		}
	}
}

void UC_GameInstance::OnDestroySessionComplete ( FName SessionName, bool bWasSuccessful ) {
	GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, FString::Printf ( TEXT ( "OnDestroySessionComplete %s, %d" ), *SessionName.ToString (), bWasSuccessful ) );

	// Get the OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get ();
	if ( OnlineSub ) {
		// Get the SessionInterface from the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();

		if ( Sessions.IsValid () ) {
			// Clear the Delegate
			Sessions->ClearOnDestroySessionCompleteDelegate_Handle ( _destroySessionCompleteDelegateHandle );

			// If it was successful, we just load another level (could be a MainMenu!)
			if ( bWasSuccessful ) {
				quittedAsServer ();
			}
		}
	}
}

bool UC_GameInstance::HostASession ( TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers ) {
	// Get the Online Subsystem to work with

	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get ();

	if ( OnlineSub ) {
		// Get the Session Interface, so we can call the "CreateSession" function on it
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();

		if ( Sessions.IsValid () && UserId.IsValid () ) {
			/*
			Fill in all the Session Settings that we want to use.

			There are more with SessionSettings.Set(...);
			For example the Map or the GameMode/Type.
			*/
			SessionSettings = MakeShareable ( new FOnlineSessionSettings () );

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			SessionSettings->Set ( SETTING_MAPNAME, FString ( "NewMap" ), EOnlineDataAdvertisementType::ViaOnlineService );

			// Set the delegate to the Handle of the SessionInterface
			_createSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle ( _createSessionCompleteDelegate );

			// Our delegate should get called when this is complete (doesn't need to be successful!)
			return Sessions->CreateSession ( *UserId, SessionName, *SessionSettings );
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage ( -1, 10.f, FColor::Red, TEXT ( "No OnlineSubsytem found!" ) );
	}

	return false;
}

void UC_GameInstance::FindSessions ( TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence ) {
	// Get the OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get ();

	if ( OnlineSub ) {
		// Get the SessionInterface from our OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();

		if ( Sessions.IsValid () && UserId.IsValid () ) {
			/*
			Fill in all the SearchSettings, like if we are searching for a LAN game and how many results we want to have!
			*/
			SessionSearch = MakeShareable ( new FOnlineSessionSearch () );

			SessionSearch->bIsLanQuery = bIsLAN;
			SessionSearch->MaxSearchResults = 20;
			SessionSearch->PingBucketSize = 50;

			// We only want to set this Query Setting if "bIsPresence" is true
			if ( bIsPresence ) {
				SessionSearch->QuerySettings.Set ( SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals );
			}

			TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef ();

			// Set the Delegate to the Delegate Handle of the FindSession function
			_findSessionsCompleteDelegateHandle = Sessions->AddOnFindSessionsCompleteDelegate_Handle ( _findSessionsCompleteDelegate );

			// Finally call the SessionInterface function. The Delegate gets called once this is finished

			Sessions->FindSessions ( *UserId, SearchSettingsRef );
		}
	}
	else {
		// If something goes wrong, just call the Delegate Function directly with "false".

		OnFindSessionsComplete ( false );
	}
}

bool UC_GameInstance::JoinASession ( TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult ) {
	// Return bool
	bool bSuccessful = false;

	// Get OnlineSubsystem we want to work with
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get ();

	if ( OnlineSub ) {
		// Get SessionInterface from the OnlineSubsystem
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();

		if ( Sessions.IsValid () && UserId.IsValid () ) {
			// Set the Handle again
			_joinSessionCompleteDelegateHandle = Sessions->AddOnJoinSessionCompleteDelegate_Handle ( _joinSessionCompleteDelegate );

			// Call the "JoinSession" Function with the passed "SearchResult". The "SessionSearch->SearchResults" can be used to get such a
			// "FOnlineSessionSearchResult" and pass it. Pretty straight forward!
			bSuccessful = Sessions->JoinSession ( *UserId, SessionName, SearchResult );
		}
	}

	return bSuccessful;
}

UC_GameInstance::UC_GameInstance (){
	_createSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject ( this, &UC_GameInstance::OnCreateSessionComplete );
	_startSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject ( this, &UC_GameInstance::OnStartOnlineGameComplete );
	_findSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject ( this, &UC_GameInstance::OnFindSessionsComplete );
	_joinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject ( this, &UC_GameInstance::OnJoinSessionComplete );
	_destroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject ( this, &UC_GameInstance::OnDestroySessionComplete );
}

void UC_GameInstance::startAsServer () {
	HostASession ( GetFirstGamePlayer ()->GetPreferredUniqueNetId (), GameSessionName, true, true, 2 );
}

TArray<FBPOnlineSessionSearchResult> UC_GameInstance::searchAsClient () {
	ULocalPlayer* const Player = GetFirstGamePlayer ();

	FindSessions ( Player->GetPreferredUniqueNetId (), GameSessionName, true, true );
	TArray<FBPOnlineSessionSearchResult> ret;

	if ( SessionSearch->SearchResults.Num () > 0 ) {
		for ( int32 i = 0; i < SessionSearch->SearchResults.Num (); i++ ) {
			// To avoid something crazy, we filter sessions from ourself
			if ( SessionSearch->SearchResults[i].Session.OwningUserId != Player->GetPreferredUniqueNetId () ) {
				FBPOnlineSessionSearchResult BP_Result;
				auto Result = SessionSearch->SearchResults[i];
				BP_Result.GetSessionIdStr = Result.GetSessionIdStr ();
				BP_Result.id = i;
				BP_Result.IsValid = Result.IsValid ();
				BP_Result.PingInMs = Result.PingInMs;
				ret.Add ( BP_Result );
			}
		}
	}
	return ret;
}

void UC_GameInstance::joinAsClient ( FBPOnlineSessionSearchResult res) {
	ULocalPlayer* const Player = GetFirstGamePlayer ();

	// Just a SearchResult where we can save the one we want to use, for the case we find more than one!
	// If the Array is not empty, we can go through it
	JoinASession ( Player->GetPreferredUniqueNetId (), GameSessionName, SessionSearch->SearchResults[res.id] );
}

void UC_GameInstance::quitAsServer () {
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get ();
	if ( OnlineSub ) {
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface ();

		if ( Sessions.IsValid () ) {
			Sessions->AddOnDestroySessionCompleteDelegate_Handle ( _destroySessionCompleteDelegate );

			Sessions->DestroySession ( GameSessionName );
		}
	}
}
