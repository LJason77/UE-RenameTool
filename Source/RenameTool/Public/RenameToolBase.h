// Copyright (c) 2024, LJason. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "EditorUtilityWidgetComponents.h"
#include "RenameToolBase.generated.h"

class UTextBlock;
class URenameResult;
class UDetailsView;

/**
 * 重命名工具
 */
UCLASS(Abstract)
class RENAMETOOL_API URenameToolBase : public UEditorUtilityWidget
{
    GENERATED_BODY()

public:
    /** 正则表达式 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenameDetails", meta = (DisplayName = "正则表达式"))
    bool Regex = true;

    /** 搜索 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenameDetails", meta = (DisplayName = "搜索"))
    FString Search = {};

    /** 替换 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RenameDetails", meta = (DisplayName = "替换"))
    FString Replace;

    UPROPERTY(EditDefaultsOnly, Category = "RenameResult")
    TSubclassOf<URenameResult> RenameResult = nullptr;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    void BindAll();
    void UnBindAll() const;

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UDetailsView> DetailsView = nullptr;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> PreviewResult = nullptr;

    UPROPERTY(meta = (BindWidget, EntryClass = URenameResult))
    TObjectPtr<UEditorUtilityListView> PreviewList = nullptr;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UEditorUtilityButton> PreviewButton = nullptr;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UEditorUtilityButton> ExecuteButton = nullptr;

    TArray<FAssetData> SelectedAssets = {};

    FDelegateHandle AssetSelectionChangedDelegateHandle;

    void OnSelectionChanged(const TArray<FAssetData> &NewSelectedAssets, bool bIsPrimaryBrowser);

    FString GetRenameResult(const FText &OldName) const;
    FString GetRenameResult(const FString &OldName) const;

    /** 更新预览列表 */
    UFUNCTION()
    void UpdatePreviewList();

    /** 重命名对象 */
    UFUNCTION()
    void RenameObject();
};