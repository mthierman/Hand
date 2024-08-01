#pragma once

#include <clap/factory/plugin-factory.h>

#include <functional>

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

inline std::function<const clap_plugin*(const clap_plugin_factory*, const clap_host*, const char*)>
    create_clap_plugin;

template <typename T> auto make() -> bool {
    create_clap_plugin = [](const struct clap_plugin_factory* /* factory */,
                            const clap_host* host,
                            const char* /* plugin_id */) -> const clap_plugin* {
        auto plugin = new T(host);
        return plugin->clapPlugin();
    };

    return true;
};
} // namespace hand
