// Copyright (C) Shifty Studio, 2017

#include "DanmakuArcanaNavigationConfig.h"

FDanmakuArcanaNavigationConfig::FDanmakuArcanaNavigationConfig()
{
	Left.Remove(EKeys::Gamepad_LeftStick_Left);
	Right.Remove(EKeys::Gamepad_LeftStick_Right);
	Up.Remove(EKeys::Gamepad_LeftStick_Up);
	Down.Remove(EKeys::Gamepad_LeftStick_Down);

	Left.Emplace(EKeys::A);
	Right.Emplace(EKeys::D);
	Up.Emplace(EKeys::W);
	Down.Emplace(EKeys::S);
}

FDanmakuArcanaNavigationConfig::~FDanmakuArcanaNavigationConfig()
{

}

EUINavigation FDanmakuArcanaNavigationConfig::GetNavigationDirectionFromKey(const FKeyEvent& InKeyEvent) const
{
	if (Right.Contains(InKeyEvent.GetKey()))
	{
		return EUINavigation::Right;
	}
	else if (Left.Contains(InKeyEvent.GetKey()))
	{
		return EUINavigation::Left;
	}
	else if (Up.Contains(InKeyEvent.GetKey()))
	{
		return EUINavigation::Up;
	}
	else if (Down.Contains(InKeyEvent.GetKey()))
	{
		return EUINavigation::Down;
	}

	return EUINavigation::Invalid;
}
