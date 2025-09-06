// Copyright ASKD Games


#include "UI/Widget/KDDialogueWidget.h"

void UKDDialogueWidget::SetDilogueText(const FText& InText)
{
	if (MyTextBlock)
	{
		MyTextBlock->SetText(InText);
	}
}
