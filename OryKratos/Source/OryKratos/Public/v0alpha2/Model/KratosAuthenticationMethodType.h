#pragma once

#include "CoreMinimal.h"
#include "KratosAuthenticationMethodType.generated.h"

UENUM()
enum EKratosAuthenticationMethodType
{
	AuthMethodLinkRecovery,
	AuthMethodPassword,
	AuthMethodTotp,
	AuthMethodOidc,
	AuthMethodWebauthn,
	AuthMethodLookupSecret,
	AuthMethodLegacySession
};
