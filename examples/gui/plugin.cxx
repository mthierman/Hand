#pragma once

#include <hand/plugin.hxx>

struct GuiPlugin final : public hand::Helper {
    explicit GuiPlugin(const clap_host* host)
        : hand::Helper(host) { }

    auto implementsGui() const noexcept -> bool override { return true; }
};

CREATE_PLUGIN(GuiPlugin)
