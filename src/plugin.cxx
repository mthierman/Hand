#include <plugin/plugin.hxx>

namespace plugins::gain {
struct Plugin final : public plugin::PluginHelper<Plugin, plugin::IgnoreNone> {
    explicit Plugin(const clap_host* host)
        : plugin::PluginHelper<Plugin, plugin::IgnoreNone>(host) { }
    ~Plugin() { }
};
} // namespace plugins::gain
