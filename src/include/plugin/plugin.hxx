#pragma once

#include <cstring>
#include <functional>
#include <unordered_map>

#if PLATFORM_WINDOWS
#include "win32.hxx"
#endif

#include "helper.hxx"

#include <config/config.hxx>

namespace plugin {

template <typename T>
std::function<const clap_plugin*(const clap_plugin_descriptor*, const clap_host*)> make {
    [](const clap_plugin_descriptor* descriptor, const clap_host* host) -> const clap_plugin* {
    auto plugin = new T(descriptor, host);
    return plugin->clapPlugin();
}
};

auto create(const clap_plugin_descriptor* descriptor, const clap_host* host) -> const clap_plugin*;

namespace event {
    auto run_loop(const clap_process* process,
                  std::function<void(const clap_event_header* event)> eventHandler)
        -> clap_process_status;
} // namespace event

namespace factory {
    auto get_plugin_count(const clap_plugin_factory* factory) -> uint32_t;
    auto get_plugin_descriptor(const clap_plugin_factory* factory,
                               uint32_t index) -> const clap_plugin_descriptor*;
    auto create_plugin(const struct clap_plugin_factory* factory,
                       const clap_host_t* host,
                       const char* plugin_id) -> const clap_plugin*;
} // namespace factory

namespace entry {
    auto init(const char* plugin_path) -> bool;
    auto deinit(void) -> void;
    auto get_factory(const char* factory_id) -> const void*;
} // namespace entry
} // namespace plugin
