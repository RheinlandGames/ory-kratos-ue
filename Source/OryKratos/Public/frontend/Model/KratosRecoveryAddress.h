#pragma once

#include "CoreMinimal.h"
#include "KratosRecoveryAddress.generated.h"

USTRUCT()
struct ORYKRATOS_API FKratosRecoveryAddress
{
	GENERATED_BODY()

	UPROPERTY() FString id;
	UPROPERTY() FString value;
	UPROPERTY() FString via;
	UPROPERTY() FDateTime created_at;
	UPROPERTY() FDateTime updated_at;
};
