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
using Descriptor = const clap_plugin_descriptor*;
using Host = const clap_host*;
using Plugin = const clap_plugin*;

template <typename T>
std::function<Plugin(Descriptor, Host)> make { [](Descriptor descriptor, Host host) -> Plugin {
    auto plugin = new T(descriptor, host);
    return plugin->clapPlugin();
} };

auto create(Descriptor descriptor, Host host) -> Plugin;

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
