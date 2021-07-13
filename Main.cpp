#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <experimental/filesystem>
#include <filesystem>
//namespace fs = std::filesystem;
#include <vector>
#include "Config.h"

offsets Offsets;
c_config g_configs;

/*
//SDK files to pull offsets from (Kn4ck3r's SDK's)
std::string AthenaClass = "\\SDK\\SoT_Athena_classes.hpp";
std::string EngineClass = "\\SDK\\SoT_Engine_classes.hpp";
std::string AthenaAIClass = "\\SDK\\SoT_AthenaAI_classes.hpp";
*/
//SDK files to pull offsets from (CheatGear SDK's)
std::string AthenaClass = "\\SDK\\Athena_classes.h";
std::string EngineClass = "\\SDK\\Engine_classes.h";
std::string AthenaAIClass = "\\SDK\\AthenaAI_classes.h";

int stringToInt(std::string input)
{
	unsigned int x;
	std::stringstream ss;
	ss << std::hex << input;
	ss >> x;
	return x;
}

int GetOffsetFromLine(std::string line)
{
	std::string offset = line.substr(line.find_first_of("/") + 3, line.find_first_of('(') - line.find_first_of("/") - 3);
	return stringToInt(offset);
}

int GetOffset(std::string File, std::string Class, std::string Offset)
{
	std::ifstream infile(File);
	std::string line;

	bool once = false;

	while (std::getline(infile, line))
	{
		if (line == (Class))
			once = !once;

		if (once)
			if (line.find(Offset) != std::string::npos)
				return GetOffsetFromLine(line);


	}
}

int main()
{
	std::string m_directory = std::experimental::filesystem::current_path().string();

	if (!std::experimental::filesystem::exists(m_directory + "\\SDK"))
	{
		MessageBoxA(NULL, "File Not Found", "File Not Found", 0);
		return 0;
	}

	EngineClass = m_directory + EngineClass;
	AthenaClass = m_directory + AthenaClass;
	AthenaAIClass = m_directory + AthenaAIClass;

	g_configs.init(); 
	// UWorld
	Offsets.UWorld.OwningGameInstance = GetOffset(EngineClass, "// Class Engine.World", "OwningGameInstance");
	Offsets.UWorld.PersistentLevel = GetOffset(EngineClass, "// Class Engine.World", "PersistentLevel");
	// UGameInstance
	Offsets.UGameInstance.LocalPlayers = GetOffset(EngineClass, "// Class Engine.GameInstance", "LocalPlayers");
	// ULocalPlayer
	Offsets.ULocalPlayer.PlayerController = GetOffset(EngineClass, "// Class Engine.Player", "PlayerController");
	// APlayerCameraManager
	Offsets.APlayerCameraManager.CameraCache = GetOffset(EngineClass, "// Class Engine.PlayerCameraManager", "CameraCache");
	// APlayerState
	Offsets.APlayerState.PlayerName = GetOffset(EngineClass, "// Class Engine.PlayerState", "PlayerName");
	// APlayerController
	Offsets.APlayerController.CameraManager = GetOffset(EngineClass, "// Class Engine.PlayerController", "CameraManager");
	Offsets.APlayerController.ControlRotation = GetOffset(EngineClass, "// Class Engine.PlayerController", "ControlRotation");
	Offsets.APlayerController.Pawn = GetOffset(EngineClass, "// Class Engine.Controller", "Pawn");
	// AActor
	Offsets.AActor.rootComponent = GetOffset(EngineClass, "// Class Engine.Actor", "RootComponent");
	Offsets.AActor.PlayerState = GetOffset(EngineClass, "// Class Engine.Pawn", "PlayerState");
	Offsets.AActor.HealthComponent = GetOffset(AthenaClass, "// Class Athena.AthenaCharacter", "HealthComponent");
	Offsets.AActor.WieldedItemComponent = GetOffset(AthenaClass, "// Class Athena.AthenaCharacter", "WieldedItemComponent");
	// AItemProxy
	Offsets.AItemProxy.AItemInfo = GetOffset(AthenaClass, "// Class Athena.ItemProxy", "ItemInfo");
	// AItemInfo
	Offsets.AItemInfo.UItemDesc = GetOffset(AthenaClass, "// Class Athena.ItemInfo", "Desc");
	// ABootyItemInfo
	Offsets.ABootyItemInfo.BootyType = GetOffset(AthenaClass, "// Class Athena.BootyItemInfo", "BootyType");
	Offsets.ABootyItemInfo.Rarity = GetOffset(AthenaClass, "// Class Athena.BootyItemInfo", "Rarity");
	// AShip
	Offsets.AShip.CrewOwnershipComponent = GetOffset(AthenaClass, "// Class Athena.Ship", "CrewOwnershipComponent");
	// UCrewOwnershipComponent
	Offsets.UCrewOwnershipComponent.CrewId = GetOffset(AthenaClass, "// Class Athena.CrewOwnershipComponent", "CachedCrewId");
	// ACrewService
	Offsets.ACrewService.Crews = GetOffset(AthenaClass, "// Class Athena.CrewService", "Crews");
	// AMapTable
	Offsets.AMapTable.MapPins = GetOffset(AthenaClass, "// Class Athena.MapTable", "MapPins");
	Offsets.AMapTable.ServerCenter = GetOffset(AthenaClass, "// Class Athena.MapTable", "ServerCentreLocation");
	Offsets.AMapTable.TrackedShips = GetOffset(AthenaClass, "// Class Athena.MapTable", "TrackedShips");
	// UWieldedItemComponent
	Offsets.UWieldedItemComponent.WieldedItem = GetOffset(AthenaClass, "// Class Athena.WieldedItemComponent", "CurrentlyWieldedItem");
	// AWieldableItem
	Offsets.AWieldableItem.ItemInfo = GetOffset(AthenaClass, "// Class Athena.WieldableItem", "ItemInfo");
	// AFauna
	Offsets.AFauna.Name = GetOffset(AthenaAIClass, "// Class AthenaAI.Fauna", "DisplayName");

	g_configs.save("offsets");

	system("PAUSE");

	return 0;
}