// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeWidget.h"

void UFadeWidget::FadeIn()
{
	PlayAnimation(FadeEffect);
}

void UFadeWidget::FadeOut()
{
	PlayAnimation(FadeEffect, 0, 1, EUMGSequencePlayMode::Reverse);
}