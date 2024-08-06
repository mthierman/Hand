#pragma once

#include <clap/plugin.h>

#include <vector>

namespace hand {
namespace descriptor {
    extern const char* id;
    extern const char* name;
    extern const char* vendor;
    extern const char* url;
    extern const char* manual_url;
    extern const char* support_url;
    extern const char* version;
    extern const char* description;
    extern const std::vector<const char*> features;
} // namespace descriptor

extern const clap_plugin_descriptor clap_descriptor;
} // namespace hand
