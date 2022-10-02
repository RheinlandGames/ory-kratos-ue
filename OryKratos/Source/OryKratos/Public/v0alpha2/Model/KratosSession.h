#pragma once

#include "CoreMinimal.h"
#include "KratosAuthenticationMethod.h"
#include "KratosIdentity.h"
#include "KratosSession.generated.h"

USTRUCT()
struct ORYKRATOS_API FKratosSession
{
	GENERATED_BODY()

	UPROPERTY() FString id;
	UPROPERTY() bool active;
	UPROPERTY() FDateTime expires_at;
	UPROPERTY() FDateTime issued_at;
	UPROPERTY() FDateTime authenticated_at;
	UPROPERTY() TArray<FKratosAuthenticationMethod> authentication_methods;
	UPROPERTY() FString authenticator_assurance_level;
	UPROPERTY() FKratosIdentity identity;
};
