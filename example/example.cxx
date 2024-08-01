#pragma once

#include <plugin/plugin.hxx>

struct ExamplePlugin final : public plugin::Helper<ExamplePlugin, plugin::IgnoreNone> {
    explicit ExamplePlugin(const clap_plugin_descriptor* descriptor, const clap_host* host)
        : plugin::Helper<ExamplePlugin, plugin::IgnoreNone>(descriptor, host) { }
};

auto plugin::create(const clap_plugin_descriptor* descriptor,
                    const clap_host* host) -> const clap_plugin* {
    return plugin::make<ExamplePlugin>(descriptor, host);
}
