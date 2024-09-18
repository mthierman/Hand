#include <hand/entry.hxx>
#include <hand/factory.hxx>

#include <cstring>

namespace hand::entry {
auto init(const char* /* plugin_path */) -> bool { return true; }

auto deinit(void) -> void { }

auto get_factory(const char* factory_id) -> const void* {
    return (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0) ? &hand::clap_factory : nullptr;
}
} // namespace hand::entry

extern "C" {
const CLAP_EXPORT clap_plugin_entry clap_entry { .clap_version { CLAP_VERSION },
                                                 .init { hand::entry::init },
                                                 .deinit { hand::entry::deinit },
                                                 .get_factory { hand::entry::get_factory } };
}
