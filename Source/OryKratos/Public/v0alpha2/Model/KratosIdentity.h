#pragma once

#include "CoreMinimal.h"
#include "KratosCredentials.h"
#include "KratosRecoveryAddress.h"
#include "KratosVerifiableAddress.h"
#include "KratosIdentity.generated.h"

USTRUCT()
struct ORYKRATOS_API FKratosIdentity
{
	GENERATED_BODY()

	UPROPERTY() FString id;
	UPROPERTY() FString schema_id;
	UPROPERTY() FString schema_url;
	UPROPERTY() FString state;
	UPROPERTY() FDateTime state_changed_at;
	UPROPERTY() TMap<FString, FKratosCredentials> credentials;
	UPROPERTY() TArray<FKratosRecoveryAddress> recovery_addresses;
	UPROPERTY() TArray<FKratosVerifiableAddress> verifiable_addresses;
	UPROPERTY() FString metadata_admin;
	UPROPERTY() FString metadata_public;
	UPROPERTY() FDateTime created_at;
	UPROPERTY() FDateTime updated_at;
	UPROPERTY() TMap<FString, FString> traits;
};
