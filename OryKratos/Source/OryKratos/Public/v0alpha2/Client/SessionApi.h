#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "SessionApi.generated.h"

struct FKratosSession;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWhoAmICompleted, FKratosSession&);

UCLASS()
class ORYKRATOS_API USessionApi : public UObject
{
	GENERATED_BODY()

	const FString WhoAmIPath = TEXT("/sessions/whoami");

	FString BaseUrl;
	FString SessionToken;

	FHttpRequestPtr WhoAmIRequest;
	void OnWhoAmIRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);
	
public:
	void Initialize(FString ConfigBaseUrl, FString ConfigSessionToken);

	void WhoAmI() const;
	FOnWhoAmICompleted OnWhoAmICompletedDelegates;
	
};
