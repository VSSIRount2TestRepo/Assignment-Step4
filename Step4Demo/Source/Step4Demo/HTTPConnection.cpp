#include "HTTPConnection.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HAL/PlatformTime.h"

FString UHTTPConnection::connectWithHTTP(FString input)
{
    FString url = input;

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(url);
    Request->SetVerb("GET");
    Request->SetTimeout(5); // Set timeout for 5 seconds

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
        if (duration >= 5.0)
        {
            Request->CancelRequest();
            return FString(TEXT("접속실패"));
        }

        // Put this thread to sleep for 0.5 seconds to avoid maxing out the CPU core.
        FPlatformProcess::Sleep(0.5);
    }

    if (EHttpResponseCodes::IsOk(Request->GetResponse().Get()->GetResponseCode()))
    {
        return FString(TEXT("접속완료"));
    }
    else {
        return FString(TEXT("접속실패"));
    }
}