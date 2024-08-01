#pragma once

#include <clap/factory/plugin-factory.h>

#include <functional>

namespace plugin {
namespace factory {
    auto get_plugin_count(const clap_plugin_factory* factory) -> uint32_t;
    auto get_plugin_descriptor(const clap_plugin_factory* factory,
                               uint32_t index) -> const clap_plugin_descriptor*;
    auto create_plugin(const struct clap_plugin_factory* factory,
                       const clap_host* host,
                       const char* plugin_id) -> const clap_plugin*;

    auto create_plugin_callback(const clap_host* host) -> const clap_plugin*;

    inline std::function<const clap_plugin*(const clap_host* host)> create_plugin_lambda;
} // namespace factory

extern const clap_plugin_factory clap_factory;

template <typename T> auto make() -> bool {
    factory::create_plugin_lambda = [](const clap_host* host) -> const clap_plugin* {
        auto plugin = new T(host);
        return plugin->clapPlugin();
    };

    return true;
};
} // namespace plugin