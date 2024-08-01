// clang-format off
#pragma once

#include <clap/plugin.h>

#include <array>

namespace hand {
namespace descriptor {
    constexpr const char* id { "@PLUGIN_ID@" };
    constexpr const char* name { "@PLUGIN_NAME@" };
    constexpr const char* vendor { "@PLUGIN_VENDOR@" };
    constexpr const char* url { "@PLUGIN_URL@" };
    constexpr const char* manual_url { "@PLUGIN_MANUAL_URL@" };
    constexpr const char* support_url { "@PLUGIN_SUPPORT_URL@" };
    constexpr const char* version { "@PLUGIN_VERSION@" };
    constexpr const char* description { "@PLUGIN_DESCRIPTION@" };
    constexpr std::array features { @PLUGIN_FEATURES@ };
} // namespace descriptor

extern const clap_plugin_descriptor clap_descriptor;
} // namespace hand
// clang-format on
