#pragma once

#include <hand/plugin.hxx>

struct BasicPlugin final : public hand::Helper {
    explicit BasicPlugin(const clap_host* host)
        : hand::Helper(host) { }
};

CREATE_PLUGIN(BasicPlugin)
