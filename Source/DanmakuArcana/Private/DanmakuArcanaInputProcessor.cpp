// Fill out your copyright notice in the Description page of Project Settings.

#include "DanmakuArcanaInputProcessor.h"

#include "Application/SlateApplication.h"

bool FDanmakuArcanaInputProcessor::IsKeyboardUserUsingPad = false;

FDanmakuArcanaInputProcessor::FDanmakuArcanaInputProcessor()
{

}

FDanmakuArcanaInputProcessor::~FDanmakuArcanaInputProcessor()
{
}

void FDanmakuArcanaInputProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
	// Restore any widget focus cached in the mouse button down handler
	if(CachedWidgets.Num() > 0) {
		for (TPair<int32, TSharedPtr<SWidget>> Pair : CachedWidgets) {
			SlateApp.SetUserFocus(Pair.Key, Pair.Value, EFocusCause::SetDirectly);
		}

		CachedWidgets.Empty();
	}
}

bool FDanmakuArcanaInputProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetUserIndex() == SlateApp.GetUserIndexForKeyboard()) {
		FDanmakuArcanaInputProcessor::IsKeyboardUserUsingPad = InKeyEvent.GetKey().IsGamepadKey();
	}

	// Ignore key repeats
	if(InKeyEvent.IsRepeat())
	{
		return true;
	}

	return false;
}

bool FDanmakuArcanaInputProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	// Cache non-keyboard users' focused widgets before they're voided by the game viewport's defocus handler
	SlateApp.ForEachUser([&](FSlateUser* User) {
		int32 CachedUserIndex = User->GetUserIndex();
		if (CachedUserIndex != SlateApp.GetUserIndexForKeyboard()) {
			CachedWidgets.Add(CachedUserIndex, SlateApp.GetUserFocusedWidget(CachedUserIndex));
		}
	});

	return false;
}
