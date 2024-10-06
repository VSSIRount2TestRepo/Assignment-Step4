
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TCPSocketConnection.generated.h"

/**
 *
 */
UCLASS()
class STEP4DEMO_API UTCPSocketConnection : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Connection")
	static FString connectToServer(FString ipAddress);
};
