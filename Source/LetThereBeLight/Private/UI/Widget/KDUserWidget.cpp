// Copyright ASKD Games


#include "UI/Widget/KDUserWidget.h"

void UKDUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
