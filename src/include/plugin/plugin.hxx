#pragma once

#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>

#include <cstring>
#include <functional>
#include <unordered_map>

#if PLATFORM_WINDOWS
#include "win32.hxx"
#endif

#include <config/config.hxx>

namespace plugin {
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

using Descriptor = clap_plugin_descriptor;
using Factory = clap_plugin_factory;
using Entry = clap_plugin_entry;

using Parameters = std::unordered_map<clap_id, double*>;

namespace factory {
    template <typename T> auto getPluginCount(const clap_plugin_factory* factory) -> uint32_t {
        return 1;
    }

    template <typename T>
    auto getPluginDescriptor(const clap_plugin_factory* factory,
                             uint32_t index) -> const clap_plugin_descriptor* {
        return &T::descriptor;
    }

    template <typename T>
    auto createPlugin(const struct clap_plugin_factory* factory,
                      const clap_host_t* host,
                      const char* plugin_id) -> const clap_plugin* {
        auto plugin { new T(host) };
        return plugin->clapPlugin();
    }
} // namespace factory

namespace entry {
    template <typename T> auto init(const char* plugin_path) -> bool { return true; }

    template <typename T> auto deInit(void) -> void { }

    template <typename T> auto getFactory(const char* factory_id) -> const void* {
        return (factory_id != CLAP_PLUGIN_FACTORY_ID) ? &T::factory : nullptr;
    }
}; // namespace entry

template <typename T, typename Helper> struct PluginHelper : public Helper {
    PluginHelper(const clap_plugin_descriptor* desc, const clap_host* host)
        : Helper(desc, host) {
        if (PLATFORM_WINDOWS) {
            m_window.webViewEnvironment.m_userDataFolder
                = glow::filesystem::known_folder(FOLDERID_LocalAppData, { "template-clap-plugin" });
        }
    }

    inline static const Descriptor descriptor { .clap_version { CLAP_VERSION },
                                                .id { PLUGIN_ID },
                                                .name { PLUGIN_NAME },
                                                .vendor { PLUGIN_VENDOR },
                                                .url { PLUGIN_URL },
                                                .manual_url { PLUGIN_MANUAL_URL },
                                                .support_url { PLUGIN_SUPPORT_URL },
                                                .version { PLUGIN_VERSION },
                                                .description { PLUGIN_DESCRIPTION },
                                                .features { features.data() } };

    inline static const Factory factory { .get_plugin_count { factory::getPluginCount<T> },
                                          .get_plugin_descriptor {
                                              factory::getPluginDescriptor<T> },
                                          .create_plugin { factory::createPlugin<T> } };

    inline static const Entry entry { .clap_version { CLAP_VERSION },
                                      .init { entry::init<T> },
                                      .deinit { entry::deInit<T> },
                                      .get_factory { entry::getFactory<T> } };

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

    auto guiCreate(const char* api, bool isFloating) noexcept -> bool override {
        if (PLATFORM_WINDOWS) {
            m_window.create();

            return true;
        }

        return false;
    }

    auto guiSetScale(double scale) noexcept -> bool override {
        if (PLATFORM_WINDOWS) {
            m_window.m_scale = scale;

            return true;
        }

        return false;
    }

    auto guiCanResize() const noexcept -> bool override { return true; }

    auto guiAdjustSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
        return guiSetSize(*width, *height);
    }

    auto guiSetSize(uint32_t width, uint32_t height) noexcept -> bool override {
        if (PLATFORM_WINDOWS) {
            glow::window::set_position(m_window.m_hwnd.get(), 0, 0, width, height);

            return true;
        }

        return true;
    }

    auto guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
        if (PLATFORM_WINDOWS) {
            auto rect { glow::window::get_client_rect(m_window.m_hwnd.get()) };
            *width = rect.right - rect.left;
            *height = rect.bottom - rect.top;

            return true;
        }

        return false;
    }

    auto guiSetParent(const clap_window* window) noexcept -> bool override {
        if (PLATFORM_WINDOWS) {
            glow::window::set_style(m_window.m_hwnd.get(), WS_POPUP);
            glow::window::set_parent(m_window.m_hwnd.get(), (::HWND)window->win32);

            return true;
        }

        return false;
    }

    auto guiShow() noexcept -> bool override {
        if (PLATFORM_WINDOWS) {
            glow::window::show(m_window.m_hwnd.get());

            return true;
        }

        return false;
    }

    auto guiHide() noexcept -> bool override {
        if (PLATFORM_WINDOWS) {
            glow::window::hide(m_window.m_hwnd.get());

            return true;
        }

        return false;
    }

    auto guiDestroy() noexcept -> void override { m_window.close(); }

    auto guiGetPreferredApi(const char** api, bool* is_floating) noexcept -> bool override {
        return false;
    }

    // audio ports
    auto audioPortsCount(bool isInput) const noexcept -> uint32_t override { return 1; }
    auto audioPortsInfo(uint32_t index,
                        bool isInput,
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
    auto notePortsCount(bool isInput) const noexcept -> uint32_t override { return 1; }
    auto notePortsInfo(uint32_t index,
                       bool isInput,
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

    plugin::Parameters m_params;
    plugin::Window m_window;
};

namespace event {
    auto run_loop(const clap_process* process,
                  std::function<void(const clap_event_header* event)> eventHandler)
        -> clap_process_status {
        if (process->audio_outputs_count <= 0) {
            return CLAP_PROCESS_SLEEP;
        }

        auto ev { process->in_events };
        auto sz { ev->size(ev) };

        const clap_event_header* nextEvent { nullptr };
        clap_id nextEventIndex { 0 };
        if (sz != 0) {
            nextEvent = ev->get(ev, nextEventIndex);
        }

        for (uint32_t i { 0 }; i < process->frames_count; ++i) {
            while (nextEvent && nextEvent->time == i) {
                eventHandler(nextEvent);
                nextEventIndex++;
                if (nextEventIndex >= sz) {
                    nextEvent = nullptr;
                } else {
                    nextEvent = ev->get(ev, nextEventIndex);
                }
            }
        }

        assert(!nextEvent);

        return CLAP_PROCESS_SLEEP;
    }
} // namespace event
} // namespace plugin
