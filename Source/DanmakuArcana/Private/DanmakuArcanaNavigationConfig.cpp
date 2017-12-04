// Copyright (C) Shifty Studio, 2017

#include "DanmakuArcanaNavigationConfig.h"

FDanmakuArcanaNavigationConfig::FDanmakuArcanaNavigationConfig()
{
	KeyEventRules.Emplace(EKeys::A, EUINavigation::Left);
	KeyEventRules.Emplace(EKeys::D, EUINavigation::Right);
	KeyEventRules.Emplace(EKeys::W, EUINavigation::Up);
	KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);

	bTabNavigation = false;
}

FDanmakuArcanaNavigationConfig::~FDanmakuArcanaNavigationConfig()
{

}
