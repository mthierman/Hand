#include <plugin/plugin.hxx>

namespace gain {
struct Plugin final : public plugin::PluginHelper<Plugin, plugin::IgnoreNone> {
    explicit Plugin(const clap_host* host)
        : plugin::PluginHelper<Plugin, plugin::IgnoreNone>(host) { }
    ~Plugin() { }
};
} // namespace gain

auto plugin::create(const clap_host_t* host) -> const clap_plugin* {
    auto plugin { new gain::Plugin(host) };
    return plugin->clapPlugin();
}
