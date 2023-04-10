#pragma once

#include "CoreMinimal.h"
#include "KratosSubmitPasswordLoginFlow.generated.h"

USTRUCT()
struct FKratosSubmitPasswordLoginFlow
{
	GENERATED_BODY()

	UPROPERTY() FString csrf_token;
	UPROPERTY() FString identifier;
	UPROPERTY() FString method;
	UPROPERTY() FString password;
	
};
