#include "HTTPConnection.h"
#include "HttpModule.h" 
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/IHttpResponse.h"

DEFINE_LOG_CATEGORY_STATIC(LogHTTPConnection, Log, All);

FString UHTTPConnection::connectWithHTTP(FString input)
{
    int timeOut = 10;
    FString url = input;

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(url);
    Request->SetVerb("GET");
    Request->SetTimeout(timeOut);

    Request->ProcessRequest();

    // Get the time of request initiation
    double startTime = FPlatformTime::Seconds();

    // Block until the request has completed or timed out
    while (Request->GetStatus() != EHttpRequestStatus::Failed &&
        Request->GetStatus() != EHttpRequestStatus::Failed_ConnectionError &&
        Request->GetStatus() != EHttpRequestStatus::Succeeded)
    {
        // Get the duration from request initiation until now
        double duration = FPlatformTime::Seconds() - startTime;

        // If duration has exceeded 5 seconds(timeout), stop waiting and return fail message
        if (duration >= timeOut)
        {
            Request->CancelRequest();
            UE_LOG(LogHTTPConnection, Log, TEXT("Failed to send HTTP request"));
            return FString(TEXT("접속실패"));
        }

        // Put this thread to sleep for 0.5 seconds to avoid maxing out the CPU core.
        FPlatformProcess::Sleep(0.5);
    }

    if (EHttpResponseCodes::IsOk(Request->GetResponse().Get()->GetResponseCode()))
    {   
        UE_LOG(LogHTTPConnection, Log, TEXT("Connection success"));
        return FString(TEXT("접속완료"));
    }
    else {
        UE_LOG(LogHTTPConnection, Log, TEXT("Connection failed. Rejected connection."));
        return FString(TEXT("접속실패. 연결 거부"));
    }
}