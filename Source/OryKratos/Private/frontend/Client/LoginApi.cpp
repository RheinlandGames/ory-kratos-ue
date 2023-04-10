#include "frontend/Client/LoginApi.h"

#include "JsonObjectConverter.h"
#include "frontend/Model/KratosLoginFlow.h"
#include "frontend/Model/KratosSubmitLoginFlowResponse.h"
#include "frontend/Model/KratosSubmitPasswordLoginFlow.h"
#include "Interfaces/IHttpResponse.h"

void ULoginApi::Initialize(FString ConfigBaseUrl)
{
	this->BaseUrl = ConfigBaseUrl;

	CreateLoginFlowApiRequest = FHttpModule::Get().CreateRequest();
	CreateLoginFlowApiRequest->SetVerb(TEXT("GET"));
	CreateLoginFlowApiRequest->SetURL(FString::Printf(TEXT("%s%s"), *ConfigBaseUrl, *CreateLoginFlowApiPath));
	CreateLoginFlowApiRequest->OnProcessRequestComplete().BindUObject(this, &ULoginApi::OnCreateLoginFlowApiRequestComplete);

	SubmitPasswordLoginFlowRequest = FHttpModule::Get().CreateRequest();
	SubmitPasswordLoginFlowRequest->SetVerb(TEXT("POST"));
	SubmitPasswordLoginFlowRequest->SetURL(FString::Printf(TEXT("%s%s"), *ConfigBaseUrl, *SubmitPasswordLoginFlowPath));
	SubmitPasswordLoginFlowRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	SubmitPasswordLoginFlowRequest->OnProcessRequestComplete().BindUObject(this, &ULoginApi::OnSubmitPasswordLoginFlowRequestComplete);
}

void ULoginApi::CreateLoginFlowApi(bool bRefresh, FString aal, FString sessionToken)
{
	CreateLoginFlowForNativeApps(bRefresh, aal, sessionToken);
}

void ULoginApi::ResetCreateLoginFlowForNativeAppsRequest()
{
	CreateLoginFlowApiRequest->SetURL(FString::Printf(TEXT("%s%s"), *BaseUrl, *CreateLoginFlowApiPath));
	CreateLoginFlowApiRequest->SetHeader(TEXT("X-Session-Token"), TEXT(""));
}

void ULoginApi::CreateLoginFlowForNativeApps(bool bRefresh, FString aal, FString sessionToken)
{
	ResetCreateLoginFlowForNativeAppsRequest();

	if (!sessionToken.IsEmpty())
	{
		CreateLoginFlowApiRequest->SetHeader(TEXT("X-Session-Token"), sessionToken);
	}

	CreateLoginFlowApiRequest->SetURL(FString::Printf(TEXT("%s?refresh=%s&aal=%s"), *CreateLoginFlowApiRequest->GetURL(), bRefresh ? TEXT("true") : TEXT("false"), *aal));
	CreateLoginFlowApiRequest->ProcessRequest();
}

void ULoginApi::OnCreateLoginFlowApiRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
	const int32 ResponseCode = Response->GetResponseCode();
	if (ResponseCode != EHttpResponseCodes::Ok)
	{
		UE_LOG(LogTemp, Warning, TEXT("Response code was %d"), ResponseCode)
		return;
	}

	FKratosLoginFlow LoginFlow;

	const FJsonObjectConverter* Converter = new FJsonObjectConverter();
	if (Converter->JsonObjectStringToUStruct(Response->GetContentAsString(), &LoginFlow))
	{
		OnCreateLoginFlowApiDelegates.Broadcast(LoginFlow);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not deserialize HTTP response"));
	}
}

void ULoginApi::ResetSubmitPasswordLoginFlowRequest()
{
	SubmitPasswordLoginFlowRequest->SetURL(FString::Printf(TEXT("%s%s"), *BaseUrl, *SubmitPasswordLoginFlowPath));
	SubmitPasswordLoginFlowRequest->SetHeader(TEXT("X-Session-Token"), TEXT(""));
}

void ULoginApi::SubmitPasswordLoginFlow(const FString& FlowId, FString UserIdentifier, FString Password, FString CsrfToken, const FString& sessionToken)
{
	ResetSubmitPasswordLoginFlowRequest();
	
	if (!sessionToken.IsEmpty())
	{
		SubmitPasswordLoginFlowRequest->SetHeader(TEXT("X-Session-Token"), sessionToken);
	}

	FKratosSubmitPasswordLoginFlow LoginFlow;
	LoginFlow.csrf_token = CsrfToken;
	LoginFlow.identifier = UserIdentifier;
	LoginFlow.method = TEXT("password");
	LoginFlow.password = Password;

	const TSharedPtr<FJsonObject> Payload = FJsonObjectConverter::UStructToJsonObject(LoginFlow);

	FString PayloadAsString;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&PayloadAsString);
	FJsonSerializer::Serialize(Payload.ToSharedRef(), Writer);
	
	SubmitPasswordLoginFlowRequest->SetURL(FString::Printf(TEXT("%s?flow=%s"), *SubmitPasswordLoginFlowRequest->GetURL(), *FlowId));
	SubmitPasswordLoginFlowRequest->SetContentAsString(PayloadAsString);

	SubmitPasswordLoginFlowRequest->ProcessRequest();
}

void ULoginApi::OnSubmitPasswordLoginFlowRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
	const int32 ResponseCode = Response->GetResponseCode();
	if (ResponseCode != EHttpResponseCodes::Ok)
	{
		UE_LOG(LogTemp, Warning, TEXT("Response code was %d"), ResponseCode)
		return;
	}

	FKratosSubmitLoginFlowResponse LoginFlowResponse;

	const FJsonObjectConverter* Converter = new FJsonObjectConverter();
	if (Converter->JsonObjectStringToUStruct(Response->GetContentAsString(), &LoginFlowResponse))
	{
		OnSubmitPasswordLoginFlowDelegates.Broadcast(LoginFlowResponse);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not deserialize HTTP response"));
	}
}
