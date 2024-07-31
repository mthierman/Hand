#include <plugin/plugin.hxx>

struct Plugin final : public plugin::PluginHelper<Plugin, plugin::IgnoreNone> {
    explicit Plugin(const clap_host* host)
        : plugin::PluginHelper<Plugin, plugin::IgnoreNone>(host) { }
    ~Plugin() { }
};

auto plugin::create(const clap_host_t* host) -> const clap_plugin* {
    auto plugin { new Plugin(host) };
    return plugin->clapPlugin();
}
