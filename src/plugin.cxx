#pragma once

#include <plugin/plugin.hxx>

struct ExamplePlugin final : public plugin::Helper<ExamplePlugin, plugin::IgnoreNone> {
    explicit ExamplePlugin(const clap_host* host)
        : plugin::Helper<ExamplePlugin, plugin::IgnoreNone>(host) { }
};

auto plugin::create(plugin::Host host) -> plugin::Plugin {
    return plugin::make<ExamplePlugin>(host);
}
