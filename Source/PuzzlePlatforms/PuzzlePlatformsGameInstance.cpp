// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/InGameMenu.h"

#include "PlatformTrigger.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(
	const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT
	("/Game/Blueprint/Widget/WBP_MainMenu"));
	if (MenuBPClass.Class != nullptr)
	{
		MenuClass = MenuBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT
	("/Game/Blueprint/Widget/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class != nullptr)
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}

	
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Find Class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass == nullptr) { return; }

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (Menu == nullptr) { return; }

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (InGameMenuClass == nullptr) { return; }

	UMenuWidget* GameInstanceMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (GameInstanceMenu == nullptr) { return; }

	GameInstanceMenu->Setup();
	GameInstanceMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (Engine == nullptr) { return; }
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
	
	UWorld* World = GetWorld();
	if (World == nullptr) { return; }
	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");

}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (Engine == nullptr) { return; }
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, Address);
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr)
	{
		return;
	}
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr)
	{
		return;
	}
	PlayerController->ClientTravel("/Game/Maps/MainMenu.MainMenu", ETravelType::TRAVEL_Absolute);
}
