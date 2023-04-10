#pragma once

#include "CoreMinimal.h"
#include "KratosSession.h"
#include "KratosSubmitLoginFlowResponse.generated.h"

USTRUCT()
struct FKratosSubmitLoginFlowResponse
{
	GENERATED_BODY()

	UPROPERTY() FKratosSession session;
	UPROPERTY() FString session_token;
};