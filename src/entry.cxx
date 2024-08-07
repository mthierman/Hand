#include <hand/entry.hxx>
#include <hand/factory.hxx>

namespace hand {
namespace entry {
    auto init(const char* /* plugin_path */) -> bool { return true; }

    auto deinit(void) -> void { }

    auto get_factory(const char* factory_id) -> const void* {
        return (factory_id != CLAP_PLUGIN_FACTORY_ID) ? &hand::clap_factory : nullptr;
    }
} // namespace entry
} // namespace hand
