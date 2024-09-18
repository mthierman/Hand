#include <hand/helper.hxx>

namespace hand {
Helper::Helper(const clap_host* host)
    : clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                            clap::helpers::CheckingLevel::Maximal>(&descriptor::clap_descriptor,
                                                                   host) { }

// params
auto Helper::paramsCount() const noexcept -> uint32_t override {
    return static_cast<uint32_t>(params.size());
}

// gui
auto Helper::guiIsApiSupported(const char* api, bool isFloating) noexcept -> bool override {
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

auto Helper::guiCreate(const char* /* api */, bool /* isFloating */) noexcept -> bool override {
    return gui.create();
}

auto Helper::guiSetScale(double scale) noexcept -> bool override { return gui.setScale(scale); }

auto Helper::guiCanResize() const noexcept -> bool override { return true; }

auto Helper::guiAdjustSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
    return guiSetSize(*width, *height);
}

auto Helper::guiSetSize(uint32_t width, uint32_t height) noexcept -> bool override {
    return gui.setSize(width, height);
}

auto Helper::guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
    return gui.getSize(width, height);
}

auto Helper::guiSetParent(const clap_window* window) noexcept -> bool override {
    return gui.setParent(window);
}

auto Helper::guiShow() noexcept -> bool override { return gui.show(); }

auto Helper::guiHide() noexcept -> bool override { return gui.hide(); }

auto Helper::guiDestroy() noexcept -> void override { gui.destroy(); }

auto Helper::guiGetPreferredApi(const char** /* api */,
                                bool* /* is_floating */) noexcept -> bool override {
    return false;
}

// audio ports
auto Helper::audioPortsCount(bool /* isInput */) const noexcept -> uint32_t override { return 1; }
auto Helper::audioPortsInfo(uint32_t index,
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
auto Helper::notePortsCount(bool /* isInput */) const noexcept -> uint32_t override { return 1; }
auto Helper::notePortsInfo(uint32_t index,
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
} // namespace hand
