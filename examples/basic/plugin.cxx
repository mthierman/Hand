#pragma once

#include <hand/plugin.hxx>

struct BasicPlugin final : public hand::Helper<BasicPlugin, hand::IgnoreNone> {
    explicit BasicPlugin(const clap_host* host)
        : hand::Helper<BasicPlugin, hand::IgnoreNone>(host) { }
};

namespace {
auto plugin { hand::make<BasicPlugin>() };
}
