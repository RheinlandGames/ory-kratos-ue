#pragma once

#include "CoreMinimal.h"
#include "KratosAuthenticationMethod.generated.h"

USTRUCT()
struct ORYKRATOS_API FKratosAuthenticationMethod
{
	GENERATED_BODY()

	UPROPERTY() FString method;
	UPROPERTY() FString aal;
	UPROPERTY() FDateTime completed_at;
};
