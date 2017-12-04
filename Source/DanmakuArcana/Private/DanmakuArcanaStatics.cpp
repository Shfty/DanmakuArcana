// Fill out your copyright notice in the Description page of Project Settings.

#include "DanmakuArcanaStatics.h"

#include "Components/ActorComponent.h"
#include "Regex.h"
#include "Application/SlateApplication.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"
#include "DanmakuArcanaInputProcessor.h"
#include "DanmakuArcanaNavigationConfig.h"

UActorComponent* UDanmakuArcanaStatics::AddActorComponent(AActor* Outer, UClass* ActorComponentClass)
{
	UClass * BaseClass = FindObject<UClass>(ANY_PACKAGE, TEXT("ActorComponent"));
	if(ActorComponentClass->IsChildOf(BaseClass))
	{
		UActorComponent* NewComp = NewObject<UActorComponent>(Outer, ActorComponentClass);
		if(!NewComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("AddActorComponent: Construction failed, aborting"));
			return nullptr;
		}

		NewComp->SetIsReplicated(true);
		NewComp->RegisterComponent();

		return NewComp;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AddActorComponent: Requested class is not a child of UActorComponent, aborting"));
		return nullptr;
	}
}

bool UDanmakuArcanaStatics::MatchRegex(FString Source, FString Pattern)
{
	const FRegexPattern RegexPattern(Pattern);
	FRegexMatcher RegexMatcher(RegexPattern, Source);

	return RegexMatcher.FindNext();
}

TSharedPtr<FDanmakuArcanaInputProcessor> InputProcessor;
void UDanmakuArcanaStatics::RegisterInputProcessor()
{
	if(!InputProcessor.IsValid())
	{
		InputProcessor = TSharedPtr<FDanmakuArcanaInputProcessor>(new FDanmakuArcanaInputProcessor());
	}

	FSlateApplication& SlateApp = FSlateApplication::Get();
	SlateApp.RegisterInputPreProcessor(InputProcessor);
}

void UDanmakuArcanaStatics::UnregisterInputProcessor()
{
	FSlateApplication& SlateApp = FSlateApplication::Get();
	SlateApp.UnregisterInputPreProcessor(InputProcessor);
}

void UDanmakuArcanaStatics::RegisterNavigationConfig()
{
	FSlateApplication& SlateApp = FSlateApplication::Get();
	SlateApp.SetNavigationConfigFactory([]() -> TSharedRef<FNavigationConfig> {
		return MakeShareable(new FDanmakuArcanaNavigationConfig());
	});
}

void UDanmakuArcanaStatics::UnregisterNavigationConfig()
{
	FSlateApplication& SlateApp = FSlateApplication::Get();
	SlateApp.SetNavigationConfigFactory([]() -> TSharedRef<FNavigationConfig> {
		return MakeShareable(new FNavigationConfig());
	});
}

int32 UDanmakuArcanaStatics::GetKeyboardUserIndex()
{
	return FSlateApplication::Get().GetUserIndexForKeyboard();
}

bool UDanmakuArcanaStatics::IsKeyboardUserUsingPad()
{
	return FDanmakuArcanaInputProcessor::IsKeyboardUserUsingPad;
}

// Sets user focus without interrupting non-keyboard users
void UDanmakuArcanaStatics::SetUserFocus(APlayerController* PlayerController, UWidget* WidgetToFocus)
{
	if (PlayerController == nullptr)
	{
		return;
	}

	int32 UserIndex = UGameplayStatics::GetPlayerControllerID(PlayerController);
	if (UserIndex == -1)
	{
		return;
	}

	if (WidgetToFocus == nullptr)
	{
		return;
	}

	TSharedPtr<SWidget> CachedWidget = WidgetToFocus->GetCachedWidget();
	if (!CachedWidget.IsValid())
	{
		return;
	}

	FSlateApplication& SlateApp = FSlateApplication::Get();
	TMap<int32, TSharedPtr<SWidget>> CachedWidgets;

	if (UserIndex == SlateApp.GetUserIndexForKeyboard()) {
		SlateApp.ForEachUser([&](FSlateUser* User) {
			int32 CachedUserIndex = User->GetUserIndex();
			if (CachedUserIndex != UserIndex) {
				CachedWidgets.Add(CachedUserIndex, SlateApp.GetUserFocusedWidget(CachedUserIndex));
			}
		});

		SlateApp.SetUserFocus(UserIndex, CachedWidget);

		SlateApp.ForEachUser([&](FSlateUser* User) {
			int32 CachedUserIndex = User->GetUserIndex();
			if (CachedUserIndex != UserIndex) {
				SlateApp.SetUserFocus(CachedUserIndex, *CachedWidgets.Find(CachedUserIndex), EFocusCause::SetDirectly);
			}
		});
	}
	else
	{
		SlateApp.SetUserFocus(UserIndex, CachedWidget);
	}
}

// Sets user focus to game viewport without interrupting non-keyboard users
void UDanmakuArcanaStatics::SetUserFocusToGameViewport(APlayerController* PlayerController)
{
	int32 UserIndex = UGameplayStatics::GetPlayerControllerID(PlayerController);

	if (UserIndex == -1)
	{
		return;
	}

	FSlateApplication& SlateApp = FSlateApplication::Get();
	TMap<int32, TSharedPtr<SWidget>> CachedWidgets;

	if (UserIndex == SlateApp.GetUserIndexForKeyboard()) {
		SlateApp.ForEachUser([&](FSlateUser* User) {
			int32 CachedUserIndex = User->GetUserIndex();
			if (CachedUserIndex != UserIndex) {
				CachedWidgets.Add(CachedUserIndex, SlateApp.GetUserFocusedWidget(CachedUserIndex));
			}
		});

		SlateApp.SetUserFocusToGameViewport(UserIndex);

		SlateApp.ForEachUser([&](FSlateUser* User) {
			int32 CachedUserIndex = User->GetUserIndex();
			if (CachedUserIndex != UserIndex) {
				SlateApp.SetUserFocus(CachedUserIndex, *CachedWidgets.Find(CachedUserIndex), EFocusCause::SetDirectly);
			}
		});
	}
	else
	{
		SlateApp.SetUserFocusToGameViewport(UserIndex);
	}
}

