#pragma once

#include <hand/plugin.hxx>

struct GuiPlugin final : public hand::Helper<GuiPlugin, hand::IgnoreNone> {
    explicit GuiPlugin(const clap_host* host)
        : hand::Helper<GuiPlugin, hand::IgnoreNone>(host) { }
};

namespace {
auto plugin { hand::make<GuiPlugin>() };
}
