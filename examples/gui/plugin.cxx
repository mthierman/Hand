#pragma once

#include <hand/plugin.hxx>

namespace gui {
struct GuiPlugin final : public hand::Helper<GuiPlugin, hand::IgnoreNone> {
    explicit GuiPlugin(const clap_host* host)
        : hand::Helper<GuiPlugin, hand::IgnoreNone>(host) { }
};

auto plugin { hand::make<GuiPlugin>() };
} // namespace gui