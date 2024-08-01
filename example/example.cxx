#pragma once

#include <hand/plugin.hxx>

struct ExamplePlugin final : public hand::Helper<ExamplePlugin, hand::IgnoreNone> {
    explicit ExamplePlugin(const clap_host* host)
        : hand::Helper<ExamplePlugin, hand::IgnoreNone>(host) { }
};

namespace {
auto examplePlugin { hand::make<ExamplePlugin>() };
}
