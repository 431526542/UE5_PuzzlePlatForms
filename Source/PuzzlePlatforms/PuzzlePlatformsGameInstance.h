// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
class UUserWidget;

UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : 
	public UGameInstance , public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

public:
	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();

	UFUNCTION(Exec)
	void Host(FString ServerName) override;

	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	virtual void LoadMainMenu() override;

	virtual void RefreshServerList() override;

private:
	TSubclassOf<UUserWidget> MenuClass;
	TSubclassOf<UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplate(FName SesstionName, bool Success);
	void OnDestroySesstionComplate(FName SesstionName, bool Success);
	void OnFindSessionComplate(bool Success);
	void OnJoinSessionComplate(FName SessionName,
		EOnJoinSessionCompleteResult::Type Result);

	FString DesiredServerName;
	void CreateSession();
};
