#include <plugin/plugin.hxx>

struct ExamplePlugin final : public plugin::Helper<ExamplePlugin, plugin::IgnoreNone> {
    explicit ExamplePlugin(const clap_host* host)
        : plugin::Helper<ExamplePlugin, plugin::IgnoreNone>(host) { }
    ~ExamplePlugin() { }
};

auto plugin::create(const clap_host_t* host) -> const clap_plugin* {
    return plugin::instance<ExamplePlugin>(host);
}
