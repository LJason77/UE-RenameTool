// Copyright (c) 2024, LJason. All rights reserved.

#include "RenameTool.h"

#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "RenameToolBase.h"

#define LOCTEXT_NAMESPACE "FRenameToolModule"

void FRenameToolModule::StartupModule()
{
    // 注册菜单系统初始化时调用的函数
    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FRenameToolModule::RegisterMenuExtensions));
}

void FRenameToolModule::ShutdownModule()
{
    // 注销菜单系统初始化时调用的函数
    UToolMenus::UnRegisterStartupCallback(this);

    // 注销菜单扩展
    UToolMenus::UnregisterOwner(this);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void FRenameToolModule::StartWidget()
{
    // EUW_RenameTool 路径
    // 因为是在插件里并且不会更改位置，所以可以写死路径
    const FSoftObjectPath WidgetAssetPath("/RenameTool/EUW_RenameTool.EUW_RenameTool");
    UEditorUtilityWidgetBlueprint *RenameTool = CastChecked<UEditorUtilityWidgetBlueprint>(WidgetAssetPath.TryLoad());
    UEditorUtilitySubsystem *EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
    EditorUtilitySubsystem->SpawnAndRegisterTab(RenameTool);
}

void FRenameToolModule::RegisterMenuExtensions()
{
    FToolMenuOwnerScoped OwnerScoped(this);

    // 在内容浏览器工具栏添加一个按钮
    UToolMenu *Menu = UToolMenus::Get()->ExtendMenu("MainFrame.MainMenu.Tools");
    FToolMenuSection &Section = Menu->FindOrAddSection("Tools", LOCTEXT("Tools", "工具"));

    Section.AddMenuEntry(
        FName("RenameTools"),
        LOCTEXT("RenameTools", "重命名工具"),
        LOCTEXT("RenameTools", "重命名工具"),
        FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Audit"),
        FUIAction(FExecuteAction::CreateRaw(this, &FRenameToolModule::StartWidget)));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRenameToolModule, RenameTool)