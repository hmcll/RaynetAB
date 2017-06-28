#pragma once

#include "Enums_and_Structs.generated.h"

const bool TERMINALCARD_UNUSED = false;
const bool TERMINALCARD_USED = true;

UENUM ( BlueprintType )
enum class WinState: uint8 {
	Normal, Win, fail,
};

UENUM(BlueprintType)
enum class RoundRefreshState: uint8 {
	Host, Client, None
};

UENUM ( BlueprintType )
enum class ShowType:uint8 {
	Back,
	Link,
	Virus,
	FireWall,
	Null,
};

UENUM ( BlueprintType )
enum class TerminalCard: uint8 {
	LineBoost = 0, Firewall = 1, VirusCheck = 2, NotFound = 3
};

UENUM ( BlueprintType )
enum class ServerShowingOff: uint8 {
	Link, Virus, Null
};

UENUM ( BlueprintType )
enum class EGameState: uint8 {
	Waiting,
	Starting,
	Setting_BothNotFinished,
	Setting_OneSideNotFinished,
	Setting_BothFinished,
	Playing,
	Ending
};

USTRUCT ( BlueprintType )
struct FPawnType {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "PawnType")
		int32 playerid;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool _IsShowingOff = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool _IsMovePoint = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool _IsLineBoosting = false;
	//UPROPERTY (  BlueprintReadWrite, Category = "PawnType" )
	//	bool _IsSelected = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		ShowType _Type;
};

USTRUCT ( BlueprintType )
struct FMove_C {
	GENERATED_BODY ()

	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool IsTerminal = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		bool AdditionalInfo = false;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		FVector2D MoveFrom;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		FVector2D MoveTo;
	UPROPERTY ( BlueprintReadWrite, Category = "PawnType" )
		TerminalCard Type;
};
