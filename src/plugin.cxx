#include <plugin/plugin.hxx>

namespace plugins::gain {
struct Plugin final : public plugin::PluginHelper<Plugin, plugin::IgnoreNone> {
    explicit Plugin(const clap_host* host)
        : plugin::PluginHelper<Plugin, plugin::IgnoreNone>(&descriptor, host) { }
    ~Plugin() { }
};

extern "C" {
const CLAP_EXPORT plugin::Entry clap_entry { plugins::gain::Plugin::entry };
}
} // namespace plugins::gain
