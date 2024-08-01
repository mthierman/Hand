#include <plugin/descriptor.hxx>
#include <plugin/factory.hxx>

namespace plugin {
namespace factory {
    auto get_plugin_count(const clap_plugin_factory* /* factory */) -> uint32_t { return 1; }

    auto get_plugin_descriptor(const clap_plugin_factory* /* factory */,
                               uint32_t /* index */) -> const clap_plugin_descriptor* {
        return &plugin::clap_descriptor;
    }

    auto create_plugin(const struct clap_plugin_factory* /* factory */,
                       const clap_host_t* host,
                       const char* /* plugin_id */) -> const clap_plugin* {
        return plugin::create(host);
    }
} // namespace factory

const clap_plugin_factory clap_factory { .get_plugin_count { plugin::factory::get_plugin_count },
                                         .get_plugin_descriptor {
                                             plugin::factory::get_plugin_descriptor },
                                         .create_plugin { plugin::factory::create_plugin } };
} // namespace plugin
