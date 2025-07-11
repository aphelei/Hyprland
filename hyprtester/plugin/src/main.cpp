#include <unistd.h>
#include <src/includes.hpp>
#include <sstream>
#include <any>

#define private public
#include <src/config/ConfigManager.hpp>
#include <src/config/ConfigDescriptions.hpp>
#undef private

#include "globals.hpp"

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

static SDispatchResult test(std::string in) {
    bool        success = true;
    std::string errors  = "";

    if (g_pConfigManager->m_configValueNumber != CONFIG_OPTIONS.size() + 1 /* autogenerated is special */) {
        errors += "config value number mismatches descriptions size\n";
        success = false;
    }

    return SDispatchResult{
        .success = success,
        .error   = errors,
    };
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    HyprlandAPI::addDispatcherV2(PHANDLE, "plugin:test:test", ::test);

    return {"hyprtestplugin", "hyprtestplugin", "Vaxry", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    ;
}
