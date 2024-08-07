#include <hand/descriptor.hxx>
#include <hand/factory.hxx>

namespace hand {
namespace factory {
    auto get_plugin_count(const clap_plugin_factory* /* factory */) -> uint32_t { return 1; }

    auto get_plugin_descriptor(const clap_plugin_factory* /* factory */,
                               uint32_t /* index */) -> const clap_plugin_descriptor* {
        return &hand::clap_descriptor;
    }
} // namespace factory

const clap_plugin_factory clap_factory { .get_plugin_count { hand::factory::get_plugin_count },
                                         .get_plugin_descriptor {
                                             hand::factory::get_plugin_descriptor },
                                         .create_plugin { hand::factory::create_plugin } };
} // namespace hand
