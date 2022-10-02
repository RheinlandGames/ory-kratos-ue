#pragma once

#include "CoreMinimal.h"
#include "KratosVerifiableAddress.generated.h"

USTRUCT()
struct ORYKRATOS_API FKratosVerifiableAddress
{
	GENERATED_BODY()

	UPROPERTY() FString id;
	UPROPERTY() FString value;
	UPROPERTY() bool verified;
	UPROPERTY() FString via;
	UPROPERTY() FString status;
	UPROPERTY() FDateTime created_at;
	UPROPERTY() FDateTime updated_at;
	UPROPERTY() FDateTime verified_at;
};
