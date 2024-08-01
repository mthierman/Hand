#pragma once

#include <hand/plugin.hxx>

namespace basic {
struct BasicPlugin final : public hand::Helper<BasicPlugin, hand::IgnoreNone> {
    explicit BasicPlugin(const clap_host* host)
        : hand::Helper<BasicPlugin, hand::IgnoreNone>(host) { }
};

auto plugin { hand::make<BasicPlugin>() };
} // namespace basic
