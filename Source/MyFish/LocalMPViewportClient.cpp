// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFish.h"
#include "LocalMPViewportClient.h"

//bool ULocalMPViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
//{
//	if (IgnoreInput() || bGamepad || Key.IsMouseButton())
//	{
//		return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
//	}
//	else
//	{
//		// Propagate keyboard events to all players
//		UEngine* const Engine = GetOuterUEngine();
//		int32 const NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
//		bool bRetVal = false;
//		for (int32 i = 0; i < NumPlayers; i++)
//		{
//			bRetVal = Super::InputKey(Viewport, i, Key, EventType, AmountDepressed, bGamepad) || bRetVal;
//		}
//
//		return bRetVal;
//	}
//}

void ULocalMPViewportClient::PostInitProperties()
{
	Super::PostInitProperties();

	P2Keys.Add(EKeys::O);
	P2Keys.Add(EKeys::L);
	P2Keys.Add(EKeys::Semicolon);
	P2Keys.Add(EKeys::K);
	P2Keys.Add(EKeys::P);
	P2Keys.Add(EKeys::I);
	P2Keys.Add(EKeys::RightMouseButton);
}

bool ULocalMPViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	if (P2Keys.Find(Key))
	{
		ControllerId = 1;
	}

	return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
}

