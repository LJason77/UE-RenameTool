// Copyright (c) 2024, LJason. All rights reserved.


#include "RenameToolBase.h"

#include "AssetSelection.h"
#include "ContentBrowserModule.h"
#include "EditorUtilityLibrary.h"
#include "RenameResult.h"
#include "RenameResultObject.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Editor/ScriptableEditorWidgets/Public/Components/DetailsView.h"
#include "Kismet/KismetStringLibrary.h"

void URenameToolBase::UpdatePreviewList()
{
    PreviewList->ClearListItems();
    PreviewResult->SetVisibility(SelectedAssets.Num() > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

    for (FAssetData SelectedAsset : SelectedAssets)
    {
        if (!SelectedAsset.IsValid()) continue;

        URenameResultObject *Object = NewObject<URenameResultObject>();
        FText OldName = FText::FromName(SelectedAsset.AssetName);
        Object->OldNameText = OldName;
        Object->NewNameText = FText::FromString(GetRenameResult(OldName));

        PreviewList->AddItem(Object);
    }
}

void URenameToolBase::NativeConstruct()
{
    Super::NativeConstruct();

    TabDisplayName = NSLOCTEXT("FRenameToolModule", "RenameTool", "重命名工具");

    BindAll();

    if (DetailsView)
    {
        DetailsView->SetObject(this);
    }

    SelectedAssets.Empty();

    UpdatePreviewList();
}

void URenameToolBase::NativeDestruct()
{
    UnBindAll();

    Super::NativeDestruct();
}

void URenameToolBase::BindAll()
{
    if (FModuleManager::Get().IsModuleLoaded("ContentBrowser"))
    {
        FContentBrowserModule &ContentBrowserModule = FModuleManager::GetModuleChecked<FContentBrowserModule>("ContentBrowser");
        AssetSelectionChangedDelegateHandle = ContentBrowserModule.GetOnAssetSelectionChanged().AddUObject(this, &ThisClass::OnSelectionChanged);
    }

    PreviewButton->OnClicked.AddDynamic(this, &ThisClass::UpdatePreviewList);
    ExecuteButton->OnClicked.AddDynamic(this, &ThisClass::RenameObject);
}

void URenameToolBase::UnBindAll() const
{
    if (FModuleManager::Get().IsModuleLoaded("ContentBrowser"))
    {
        FContentBrowserModule &ContentBrowserModule = FModuleManager::GetModuleChecked<FContentBrowserModule>("ContentBrowser");
        ContentBrowserModule.GetOnAssetSelectionChanged().Remove(AssetSelectionChangedDelegateHandle);
    }
}

void URenameToolBase::OnSelectionChanged(const TArray<FAssetData> &NewSelectedAssets, bool bIsPrimaryBrowser)
{
    SelectedAssets.Empty();
    SelectedAssets = NewSelectedAssets;

    UpdatePreviewList();
}

FString URenameToolBase::GetRenameResult(const FText &OldName) const
{
    return GetRenameResult(OldName.ToString());
}

FString URenameToolBase::GetRenameResult(const FString &OldName) const
{
    FString NewName = OldName;

    if (Search.IsEmpty()) return NewName;

    if (Regex)
    {
        const FRegexPattern RegexPattern(Search);
        FRegexMatcher Matcher(RegexPattern, NewName);
        while (Matcher.FindNext())
        {
            const int32 StartIndex = Matcher.GetMatchBeginning();
            const int32 EndIndex = Matcher.GetMatchEnding();

            NewName = NewName.Left(StartIndex) + Replace + NewName.Mid(EndIndex);
        }
    }
    else
    {
        NewName = UKismetStringLibrary::Replace(NewName, Search, Replace);
    }

    return NewName;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void URenameToolBase::RenameObject()
{
    for (TArray<UObject *> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets(); UObject *SelectedObject : SelectedObjects)
    {
        if (SelectedObject) UEditorUtilityLibrary::RenameAsset(SelectedObject, GetRenameResult(SelectedObject->GetName()));
    }
}