// Fill out your copyright notice in the Description page of Project Settings.

#include "DanmakuArcanaInputProcessor.h"

#include "Application/SlateApplication.h"

bool FDanmakuArcanaInputProcessor::IsKeyboardUserUsingPad = false;

FDanmakuArcanaInputProcessor::FDanmakuArcanaInputProcessor() : AnalogDeadzone(0.8f)
{
	PrevAnalogXArray.InsertZeroed(0, 4);
	PrevAnalogYArray.InsertZeroed(0, 4);
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

void SpoofKeypress(FSlateApplication& SlateApp, const FKey& Key, const int32 UserIndex) {
	FKeyEvent Event(Key, FModifierKeysState(), UserIndex, false, -1, -1);
	SlateApp.ProcessKeyDownEvent(Event);
	SlateApp.ProcessKeyUpEvent(Event);
}

bool FDanmakuArcanaInputProcessor::HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent)
{
	FKey Key = InAnalogInputEvent.GetKey();
	float AxisValue = InAnalogInputEvent.GetAnalogValue();
	int32 UserIndex = InAnalogInputEvent.GetUserIndex();

	if(Key == EKeys::Gamepad_LeftX) {
		if (AxisValue >= AnalogDeadzone && PrevAnalogXArray[UserIndex] < AnalogDeadzone) {
			SpoofKeypress(SlateApp, EKeys::Gamepad_DPad_Right, UserIndex);
		}
		else if (AxisValue <= -AnalogDeadzone && PrevAnalogXArray[UserIndex] > -AnalogDeadzone) {
			SpoofKeypress(SlateApp, EKeys::Gamepad_DPad_Left, UserIndex);
		}

		PrevAnalogXArray[UserIndex] = AxisValue;
	}
	else if (Key == EKeys::Gamepad_LeftY) {
		if (AxisValue >= AnalogDeadzone && PrevAnalogYArray[UserIndex] < AnalogDeadzone) {
			SpoofKeypress(SlateApp, EKeys::Gamepad_DPad_Up, UserIndex);
		}
		else if (AxisValue <= -AnalogDeadzone && PrevAnalogYArray[UserIndex] > -AnalogDeadzone) {
			SpoofKeypress(SlateApp, EKeys::Gamepad_DPad_Down, UserIndex);
		}

		PrevAnalogYArray[UserIndex] = AxisValue;
	}

	return false;
}
