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
