// Copyright (c) 2024, LJason. All rights reserved.


#include "RenameResult.h"

#include "EditorUtilityWidgetComponents.h"
#include "RenameResultObject.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

void URenameResult::NativeOnListItemObjectSet(UObject *ListItemObject)
{
    const URenameResultObject *Object = Cast<URenameResultObject>(ListItemObject);
    OldNameText->SetText(Object->OldNameText);
    NewNameText->SetText(Object->NewNameText);

    UpdateBackground();
}

void URenameResult::UpdateBackground() const
{
    const UEditorUtilityListView *ListView = Cast<UEditorUtilityListView>(GetOwningListView());
    const int32 Index = ListView->GetIndexForItem(GetListItem());

    BackgroundImage->SetVisibility(Index % 2 == 0 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}