// Copyright (C) Shifty Studio, 2017

#pragma once

#include "CoreMinimal.h"
#include "Application/NavigationConfig.h"

/**
 * 
 */
class DANMAKUARCANA_API FDanmakuArcanaNavigationConfig : public FNavigationConfig
{
public:
	FDanmakuArcanaNavigationConfig();
	~FDanmakuArcanaNavigationConfig();

	virtual EUINavigation GetNavigationDirectionFromKey(const FKeyEvent& InKeyEvent) const override;
};
