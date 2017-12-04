// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DanmakuArcanaStatics.generated.h"

class UActorComponent;

/**
 * 
 */
UCLASS()
class DANMAKUARCANA_API UDanmakuArcanaStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Component|AddComponent")
	static UActorComponent* AddActorComponent(AActor* Actor, UClass* ActorComponentClass);
	
	UFUNCTION(BlueprintPure, Category = "Regex")
	static bool MatchRegex(FString Source, FString Pattern);

	UFUNCTION(BlueprintCallable, Category = "Input")
	static void RegisterInputProcessor();

	UFUNCTION(BlueprintCallable, Category = "Input")
	static void UnregisterInputProcessor();

	UFUNCTION(BlueprintCallable, Category = "Input")
	static void RegisterNavigationConfig();

	UFUNCTION(BlueprintCallable, Category = "Input")
	static void UnregisterNavigationConfig();

	UFUNCTION(BlueprintPure, Category = "Input")
	static int32 GetKeyboardUserIndex();

	UFUNCTION(BlueprintPure, Category = "Input")
	static bool IsKeyboardUserUsingPad();

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	static void SetUserFocus(APlayerController* PlayerController, UWidget* WidgetToFocus);

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	static void SetUserFocusToGameViewport(APlayerController* PlayerController);
};
