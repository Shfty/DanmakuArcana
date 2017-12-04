// Copyright (C) Shifty Studio, 2017

#include "DanmakuArcanaNavigationConfig.h"

FDanmakuArcanaNavigationConfig::FDanmakuArcanaNavigationConfig()
{
	KeyEventRules.Remove(EKeys::Gamepad_LeftStick_Left);
	KeyEventRules.Remove(EKeys::Gamepad_LeftStick_Right);
	KeyEventRules.Remove(EKeys::Gamepad_LeftStick_Up);
	KeyEventRules.Remove(EKeys::Gamepad_LeftStick_Down);

	KeyEventRules.Emplace(EKeys::A, EUINavigation::Left);
	KeyEventRules.Emplace(EKeys::D, EUINavigation::Right);
	KeyEventRules.Emplace(EKeys::W, EUINavigation::Up);
	KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);

	bAnalogNavigation = false;
	bTabNavigation = false;
}

FDanmakuArcanaNavigationConfig::~FDanmakuArcanaNavigationConfig()
{

}
