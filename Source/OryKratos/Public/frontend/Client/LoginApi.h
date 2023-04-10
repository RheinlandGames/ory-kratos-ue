#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "LoginApi.generated.h"

struct FKratosLoginFlow;
struct FKratosSubmitLoginFlowResponse;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateLoginFlowApiCompleted, const FKratosLoginFlow&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubmitPasswordLoginFlowCompleted, const FKratosSubmitLoginFlowResponse&);

UCLASS()
class ORYKRATOS_API ULoginApi : public UObject
{
	GENERATED_BODY()

	const FString CreateLoginFlowApiPath = TEXT("/self-service/login/api");
	const FString SubmitPasswordLoginFlowPath = TEXT("/self-service/login");

	FString BaseUrl;

	FHttpRequestPtr CreateLoginFlowApiRequest;
	void OnCreateLoginFlowApiRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);
	void ResetSubmitPasswordLoginFlowRequest();

	FHttpRequestPtr SubmitPasswordLoginFlowRequest;
	void OnSubmitPasswordLoginFlowRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected);

public:
	void Initialize(FString ConfigBaseUrl);

	void CreateLoginFlowApi(bool bRefresh = false, FString aal = FString("aal1"), FString sessionToken = FString(""));
	void ResetCreateLoginFlowForNativeAppsRequest();
	void CreateLoginFlowForNativeApps(bool bRefresh = false, FString aal = FString("aal1"), FString sessionToken = FString(""));
	FOnCreateLoginFlowApiCompleted OnCreateLoginFlowApiDelegates;

	void SubmitPasswordLoginFlow(const FString& FlowId, FString UserIdentifier, FString Password, FString CsrfToken = FString(""), const FString& sessionToken = FString(""));
	FOnSubmitPasswordLoginFlowCompleted OnSubmitPasswordLoginFlowDelegates;
	
};
