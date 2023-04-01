#include "frontend/Client/SessionApi.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "frontend/Model/KratosSession.h"

void USessionApi::Initialize(const FString ConfigBaseUrl, const FString ConfigSessionToken)
{
	this->BaseUrl = FString(ConfigBaseUrl);
	this->SessionToken = FString(ConfigSessionToken);

	WhoAmIRequest = FHttpModule::Get().CreateRequest();
	WhoAmIRequest->SetVerb(TEXT("GET"));
	WhoAmIRequest->SetURL(FString::Printf(TEXT("%s%s"), *ConfigBaseUrl, *WhoAmIPath));
	WhoAmIRequest->SetHeader(TEXT("X-Session-Token"), ConfigSessionToken);
	WhoAmIRequest->OnProcessRequestComplete().BindUObject(this, &USessionApi::OnWhoAmIRequestComplete);
}

void USessionApi::WhoAmI() const
{
	WhoAmIRequest->ProcessRequest();
}

void USessionApi::OnWhoAmIRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnected)
{
	const int32 ResponseCode = Response->GetResponseCode();
	if (ResponseCode != EHttpResponseCodes::Ok)
	{
		UE_LOG(LogTemp, Warning, TEXT("Response code was %d"), ResponseCode)
		return;
	}

	FKratosSession Session;

	const FJsonObjectConverter* Converter = new FJsonObjectConverter();
	if (Converter->JsonObjectStringToUStruct(Response->GetContentAsString(), &Session))
	{
		OnWhoAmICompletedDelegates.Broadcast(Session);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not deserialize HTTP response"));
	}
}
