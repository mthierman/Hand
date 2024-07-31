#include <plugin/plugin.hxx>

namespace plugins::gain {
struct Plugin final : public plugin::PluginHelper<Plugin, plugin::IgnoreNone> {
    explicit Plugin(const clap_host* host)
        : plugin::PluginHelper<Plugin, plugin::IgnoreNone>(host) { }
    ~Plugin() { }
};
} // namespace plugins::gain

auto plugin::create_plugin(const struct clap_plugin_factory* /* factory */,
                   const clap_host_t* host,
                   const char* /* plugin_id */) -> const clap_plugin* {
    auto plugin { new plugins::gain::Plugin(host) };
    return plugin->clapPlugin();
}
