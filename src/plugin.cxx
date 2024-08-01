#include <plugin/plugin.hxx>

namespace plugin {
const clap_plugin_descriptor descriptor { .clap_version { CLAP_VERSION },
                                          .id { PLUGIN_ID },
                                          .name { PLUGIN_NAME },
                                          .vendor { PLUGIN_VENDOR },
                                          .url { PLUGIN_URL },
                                          .manual_url { PLUGIN_MANUAL_URL },
                                          .support_url { PLUGIN_SUPPORT_URL },
                                          .version { PLUGIN_VERSION },
                                          .description { PLUGIN_DESCRIPTION },
                                          .features { plugin::features.data() } };

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

namespace plugin::factory {
auto get_plugin_count(const clap_plugin_factory* /* factory */) -> uint32_t { return 1; }

auto get_plugin_descriptor(const clap_plugin_factory* /* factory */,
                           uint32_t /* index */) -> const clap_plugin_descriptor* {
    return &plugin::descriptor;
}

auto create_plugin(const struct clap_plugin_factory* /* factory */,
                   const clap_host_t* host,
                   const char* /* plugin_id */) -> const clap_plugin* {
    return plugin::create(host);
}
} // namespace plugin::factory

clap_plugin_factory clap_factory { .get_plugin_count { plugin::factory::get_plugin_count },
                                   .get_plugin_descriptor {
                                       plugin::factory::get_plugin_descriptor },
                                   .create_plugin { plugin::factory::create_plugin } };

namespace plugin::entry {
auto init(const char* /* plugin_path */) -> bool { return true; }

auto deinit(void) -> void { }

auto get_factory(const char* factory_id) -> const void* {
    return (factory_id != CLAP_PLUGIN_FACTORY_ID) ? &clap_factory : nullptr;
}
} // namespace plugin::entry
