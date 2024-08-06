#pragma once

#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>

#include <cstring>
#include <unordered_map>

#include "gui.hxx"
#include <hand/descriptor.hxx>

namespace hand {
using TerminateMax = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                           clap::helpers::CheckingLevel::Maximal>;
using TerminateMin = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                           clap::helpers::CheckingLevel::Minimal>;
using TerminateNone = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                            clap::helpers::CheckingLevel::None>;
using IgnoreMax = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Ignore,
                                        clap::helpers::CheckingLevel::Maximal>;
using IgnoreMin = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Ignore,
                                        clap::helpers::CheckingLevel::Minimal>;
using IgnoreNone = clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Ignore,
                                         clap::helpers::CheckingLevel::None>;
} // namespace hand

namespace hand {
template <typename T, typename U> struct Helper : public U {
    Helper(const clap_host* host)
        : U(&clap_descriptor, host) { }

    auto init() noexcept -> bool override {
        gui::init();

        return true;
    }

    // params
    auto paramsCount() const noexcept -> uint32_t override {
        return static_cast<uint32_t>(m_params.size());
    }

    // gui
    auto guiIsApiSupported(const char* api, bool isFloating) noexcept -> bool override {
        if (isFloating) {
            return false;
        }

        if (PLATFORM_WINDOWS) {
            if (std::strcmp(api, CLAP_WINDOW_API_WIN32) == 0) {
                return true;
            }
        }

        return false;
    }

    auto guiCreate(const char* /* api */, bool /* isFloating */) noexcept -> bool override {
        return gui::create();
    }

    auto guiSetScale(double scale) noexcept -> bool override { return gui::setScale(scale); }

    auto guiCanResize() const noexcept -> bool override { return true; }

    auto guiAdjustSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
        return guiSetSize(*width, *height);
    }

    auto guiSetSize(uint32_t width, uint32_t height) noexcept -> bool override {
        return gui::setSize(width, height);
    }

    auto guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
        return gui::getSize(width, height);
    }

    auto guiSetParent(const clap_window* window) noexcept -> bool override {
        return gui::setParent(window);
    }

    auto guiShow() noexcept -> bool override { return gui::show(); }

    auto guiHide() noexcept -> bool override { return gui::hide(); }

    auto guiDestroy() noexcept -> void override { gui::destroy(); }

    auto guiGetPreferredApi(const char** /* api */,
                            bool* /* is_floating */) noexcept -> bool override {
        return false;
    }

    // audio ports
    auto audioPortsCount(bool /* isInput */) const noexcept -> uint32_t override { return 1; }
    auto audioPortsInfo(uint32_t index,
                        bool /* isInput */,
                        clap_audio_port_info* info) const noexcept -> bool override {
        if (index > 0)
            return false;
        info->id = 0;
        snprintf(info->name, sizeof(info->name), "%s", "My Port Name");
        info->channel_count = 2;
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->port_type = CLAP_PORT_STEREO;
        info->in_place_pair = CLAP_INVALID_ID;
        return true;
    }

    // note ports
    auto notePortsCount(bool /* isInput */) const noexcept -> uint32_t override { return 1; }
    auto notePortsInfo(uint32_t index,
                       bool /* isInput */,
                       clap_note_port_info* info) const noexcept -> bool override {
        if (index > 0)
            return false;
        info->id = 0;
        snprintf(info->name, sizeof(info->name), "%s", "My Port Name");
        info->supported_dialects
            = CLAP_NOTE_DIALECT_CLAP | CLAP_NOTE_DIALECT_MIDI_MPE | CLAP_NOTE_DIALECT_MIDI2;
        info->preferred_dialect = CLAP_NOTE_DIALECT_CLAP;
        return true;
    }

    std::unordered_map<clap_id, double*> m_params;
};
} // namespace hand
