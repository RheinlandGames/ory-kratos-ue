#pragma once

#include "CoreMinimal.h"
#include "KratosCredentials.generated.h"

USTRUCT()
struct ORYKRATOS_API FKratosCredentials
{
	GENERATED_BODY()

	UPROPERTY() TArray<FString> identifiers;
	UPROPERTY() FString type;
	UPROPERTY() int64 version;
	UPROPERTY() FDateTime created_at;
	UPROPERTY() FDateTime updated_at;
	UPROPERTY() FString config;
};
