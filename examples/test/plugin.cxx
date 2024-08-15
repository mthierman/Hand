#pragma once

#include <hand/plugin.hxx>

struct TestPlugin final : public hand::Helper<TestPlugin, hand::IgnoreNone> {
    explicit TestPlugin(const clap_host* host)
        : hand::Helper<TestPlugin, hand::IgnoreNone>(host) { }

    auto implementsGui() const noexcept -> bool override { return true; }
};

CREATE_PLUGIN(TestPlugin)
