#pragma once

#include <plugin/plugin.hxx>

struct ExamplePlugin final : public plugin::Helper<ExamplePlugin, plugin::IgnoreNone> {
    explicit ExamplePlugin(plugin::Descriptor descriptor, plugin::Host host)
        : plugin::Helper<ExamplePlugin, plugin::IgnoreNone>(descriptor, host) { }
};

auto plugin::create(plugin::Descriptor descriptor, plugin::Host host) -> plugin::Plugin {
    return plugin::make<ExamplePlugin>(descriptor, host);
}
