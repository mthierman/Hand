#pragma once

#include <clap/plugin.h>

#include <array>

namespace hand {
namespace descriptor {
    const char* id;
    const char* name;
    const char* vendor;
    const char* url;
    const char* manual_url;
    const char* support_url;
    const char* version;
    const char* description;
    const std::array features;
} // namespace descriptor

extern const clap_plugin_descriptor clap_descriptor;
} // namespace hand
