#include "InputValidateLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(validateInput, Log, All);

bool IsValidIP(FString IP) {
    TArray<FString> Parts;
    IP.ParseIntoArray(Parts, TEXT("."));

    // Check if IP has 4 parts
    if (Parts.Num() != 4) {
        return false;
    }

    for (int i = 0; i < Parts.Num(); i++) {
        if (!Parts[i].IsNumeric()) {
            return false;
        }

        int32 PartValue = FCString::Atoi(*Parts[i]);

        if (PartValue < 0 || PartValue > 255) {
            return false;
        }
    }

    return true;
}

bool IsValidUrl(FString Url) {
    FString UrlLower = Url.ToLower();
    UE_LOG(validateInput, Log, TEXT("Got input: %s"), *UrlLower);
    // Check if it starts with http:// or https://
    if (!UrlLower.StartsWith(TEXT("http://")) && !UrlLower.StartsWith(TEXT("https://"))) {
        return false;
    }

    //More checks?

    return true;
}

/*
 * 0 - IP base with 8001 port
 * 1 - HTTP get request url
 * 2 - Invalid
 */

int UInputValidateLibrary::validateInput(FString input) {
    DEFINE_LOG_CATEGORY_STATIC(validateInput, Log, All);
    if (IsValidIP(input)) {
        UE_LOG(validateInput, Log, TEXT("Executing ip connection"));
    }
    else if (IsValidUrl(input)) {
        UE_LOG(validateInput, Log, TEXT("Executing url connection"));
        return 1;
    }
    else {
        UE_LOG(validateInput, Log, TEXT("Invalid"));
        return 2;
    }
}