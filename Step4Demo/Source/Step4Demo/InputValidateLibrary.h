// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputValidateLibrary.generated.h"

/**
 *
 */
UCLASS()
class STEP4DEMO_API UInputValidateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Connection")
	static int validateInput(FString input);
};
