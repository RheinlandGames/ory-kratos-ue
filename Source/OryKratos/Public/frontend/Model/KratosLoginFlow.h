#pragma once

#include "CoreMinimal.h"
#include "KratosLoginFlow.generated.h"

USTRUCT()
struct ORYKRATOS_API FKratosLoginFlow
{
	GENERATED_BODY()

	UPROPERTY() FString active;
	UPROPERTY() FDateTime created_at;
	UPROPERTY() FDateTime expires_at;
	UPROPERTY() FString id;
	UPROPERTY() FDateTime issued_at;
	UPROPERTY() FString oauth2_login_challenge;
	UPROPERTY() FString oauth2_login_request;
	UPROPERTY() bool refresh;
	UPROPERTY() FString request_url;
	UPROPERTY() FString requested_aal;
	UPROPERTY() FString return_to;
	UPROPERTY() FString type;
	// TODO support dynamic user interface
	// UPROPERTY() FKratosUiContainer ui;
	UPROPERTY() FDateTime updated_at;
};
