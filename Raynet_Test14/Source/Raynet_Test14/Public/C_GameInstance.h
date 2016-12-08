// Copyright(C) 2015 - 2016  Raynet AB Development Team

#pragma once

#include "Engine/GameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "C_GameInstance.generated.h"

USTRUCT ( BlueprintType )
struct FBPOnlineSessionSearchResult {
	GENERATED_USTRUCT_BODY ()

	UPROPERTY( BlueprintReadOnly )
		int32 PingInMs;
	UPROPERTY ( BlueprintReadOnly )
		bool IsValid;
	UPROPERTY ( BlueprintReadOnly )
		FString GetSessionIdStr;
	int32 id;
};

/**
 * 
 */
UCLASS()
class RAYNET_TEST14_API UC_GameInstance: public UGameInstance {
	GENERATED_BODY ()
public:

	FOnCreateSessionCompleteDelegate _createSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate _startSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate _findSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate _joinSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate _destroySessionCompleteDelegate;

	FDelegateHandle _createSessionCompleteDelegateHandle;
	FDelegateHandle _startSessionCompleteDelegateHandle;
	FDelegateHandle _findSessionsCompleteDelegateHandle;
	FDelegateHandle _joinSessionCompleteDelegateHandle;
	FDelegateHandle _destroySessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete ( FName SessionName, bool bWasSuccessful );
	void OnStartOnlineGameComplete ( FName SessionName, bool bWasSuccessful );
	void OnFindSessionsComplete ( bool bWasSuccessful );
	void OnJoinSessionComplete ( FName SessionName, EOnJoinSessionCompleteResult::Type Result );
	void OnDestroySessionComplete ( FName SessionName, bool bWasSuccessful );

	bool HostASession ( TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers );
	void FindSessions ( TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence );
	bool JoinASession ( TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult );

	UFUNCTION ( BlueprintCallable, Category = "M_Online" )
		void startAsServer ();

	UFUNCTION ( BlueprintCallable, Category = "M_Online" )
		TArray<FBPOnlineSessionSearchResult> searchAsClient ();

	UFUNCTION ( BlueprintCallable, Category = "M_Online" )
		void joinAsClient ( FBPOnlineSessionSearchResult res );

	UFUNCTION ( BlueprintCallable, Category = "M_Online" )
		void quitAsServer ();

	UFUNCTION ( BlueprintImplementableEvent )
		void startedAsServer ();

	UFUNCTION ( BlueprintImplementableEvent )
		void quittedAsServer ();

	UC_GameInstance ();
};
