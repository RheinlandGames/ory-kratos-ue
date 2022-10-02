#pragma once

#include "CoreMinimal.h"
#include "KratosCredentialsType.generated.h"

UENUM()
enum EKratosCredentialsType
{
	CredentialsPassword,
	CredentialsTotp,
	CredentialsOidc,
	CredentialsWebauthn,
	CredentialsLookupSecret
};
