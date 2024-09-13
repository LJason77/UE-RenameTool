// Copyright (c) 2024, LJason. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "RenameResult.generated.h"

class UTextBlock;
class UImage;

/**
 * 重命名结果
 */
UCLASS(Abstract)
class RENAMETOOL_API URenameResult : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

protected:
    // IUserObjectListEntry
    virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

private:
    /** 旧名称 */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> OldNameText = nullptr;

    /** 新名称 */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> NewNameText = nullptr;

    /** 背景 */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> BackgroundImage = nullptr;

    void UpdateBackground() const;
};