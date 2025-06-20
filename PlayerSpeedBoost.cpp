#ifndef DLLEXPORT
    #define DLLEXPORT __declspec(dllexport)
#endif

#include "PlayerSpeedBoost.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "RE/Skyrim.h"
#include "REL/Relocation.h"
#include "SKSE/API.h"
#include "SKSE/SKSE.h"

namespace {
    constexpr auto INI_PATH = "Data/SKSE/Plugins/PlayerSpeedBoost.ini";
    float g_speedBonus = DEFAULT_SPEED_BONUS;

    void CreateDefaultConfig() {
        std::ofstream ofs(INI_PATH);
        if (!ofs) {
            SKSE::log::warn("[PlayerSpeedBoost] Failed to create default INI at {}", INI_PATH);
            return;
        }
        ofs << "[Settings]\n";
        ofs << "fSpeedBonus=" << DEFAULT_SPEED_BONUS << "\n";
        SKSE::log::info("[PlayerSpeedBoost] Created default INI.");
    }

    void LoadConfig() {
        if (!std::filesystem::exists(INI_PATH)) {
            CreateDefaultConfig();
        }

        std::ifstream ifs(INI_PATH);
        if (!ifs) {
            SKSE::log::warn("[PlayerSpeedBoost] Could not open INI, using default");
            return;
        }

        std::string line;
        while (std::getline(ifs, line)) {
            const std::string key = "fSpeedBonus=";
            if (line.rfind(key, 0) == 0) {
                try {
                    g_speedBonus = std::stof(line.substr(key.length()));
                    SKSE::log::info("[PlayerSpeedBoost] Parsed fSpeedBonus = {}", g_speedBonus);
                } catch (...) {
                    SKSE::log::warn("[PlayerSpeedBoost] Invalid fSpeedBonus in INI");
                }
                break;
            }
        }
    }

    void BoostSpeed() {
        if (auto* player = RE::PlayerCharacter::GetSingleton(); player) {
            player->AsActorValueOwner()->RestoreActorValue(RE::ACTOR_VALUE_MODIFIER::kPermanent,
                                                           RE::ActorValue::kSpeedMult, g_speedBonus);
            SKSE::log::info("[PlayerSpeedBoost] Applied +{} SpeedMult", g_speedBonus);
        }
    }

    void OnInit() {
        SKSE::log::info("[PlayerSpeedBoost] OnInit triggered");
        LoadConfig();
        SKSE::GetTaskInterface()->AddTask([] {
            SKSE::log::info("[PlayerSpeedBoost] Applying speed boost");
            BoostSpeed();
        });
    }
}

extern "C" [[maybe_unused]] __declspec(dllexport) bool SKSEPlugin_Load(
    const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SKSE::log::info("[PlayerSpeedBoost] Plugin loaded");
    OnInit();
    return true;
}
