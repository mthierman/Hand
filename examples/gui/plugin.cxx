#pragma once

#include <hand/plugin.hxx>

struct GuiPlugin final : public hand::Helper<GuiPlugin, hand::IgnoreNone> {
    explicit GuiPlugin(const clap_host* host)
        : hand::Helper<GuiPlugin, hand::IgnoreNone>(host) { }

    auto implementsGui() const noexcept -> bool override { return true; }
};

CREATE_PLUGIN(GuiPlugin)
