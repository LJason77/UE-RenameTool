// Copyright (c) 2024, LJason. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RenameResultObject.generated.h"

/**
 * 
 */
UCLASS()
class RENAMETOOL_API URenameResultObject : public UObject
{
    GENERATED_BODY()

public:
    FText OldNameText;

    FText NewNameText;
};