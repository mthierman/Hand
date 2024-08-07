#pragma once

#include <clap/factory/plugin-factory.h>

#include <functional>

#ifndef CREATE_PLUGIN
#define CREATE_PLUGIN(PluginStruct)                                                                \
    namespace hand::factory {                                                                      \
    auto create_plugin(const struct clap_plugin_factory* factory,                                  \
                       const clap_host* host,                                                      \
                       const char* plugin_id) -> const clap_plugin* {                              \
        auto plugin { new PluginStruct(host) };                                                    \
        return plugin->clapPlugin();                                                               \
    }                                                                                              \
    } // namespace hand::factory
#endif

namespace hand {
namespace factory {
    auto get_plugin_count(const clap_plugin_factory* factory) -> uint32_t;
    auto get_plugin_descriptor(const clap_plugin_factory* factory,
                               uint32_t index) -> const clap_plugin_descriptor*;
    auto create_plugin(const struct clap_plugin_factory* factory,
                       const clap_host* host,
                       const char* plugin_id) -> const clap_plugin*;
} // namespace factory

extern const clap_plugin_factory clap_factory;
} // namespace hand
