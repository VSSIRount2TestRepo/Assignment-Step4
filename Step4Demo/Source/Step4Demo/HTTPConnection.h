// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HTTPConnection.generated.h"

/**
 * 
 */
UCLASS()
class STEP4DEMO_API UHTTPConnection : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Connection")
	static FString connectWithHTTP(FString input);
};