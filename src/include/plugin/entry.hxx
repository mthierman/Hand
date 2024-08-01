#pragma once

#include <clap/entry.h>

namespace plugin {
namespace entry {
    auto init(const char* plugin_path) -> bool;
    auto deinit(void) -> void;
    auto get_factory(const char* factory_id) -> const void*;
} // namespace entry
} // namespace plugin
