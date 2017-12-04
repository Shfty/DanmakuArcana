// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Application/IInputProcessor.h"

/**
 * 
 */
class DANMAKUARCANA_API FDanmakuArcanaInputProcessor : public IInputProcessor
{
public:
	FDanmakuArcanaInputProcessor();
	~FDanmakuArcanaInputProcessor();

	virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor);
	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent);
	virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent);
	virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent);

public:
	static bool IsKeyboardUserUsingPad;

private:
	TMap<int32, TSharedPtr<SWidget>> CachedWidgets;

	const float AnalogDeadzone;
	TArray<float> PrevAnalogXArray;
	TArray<float> PrevAnalogYArray;
};
