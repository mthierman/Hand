#include <hand/entry.hxx>
#include <hand/factory.hxx>

#include <cstring>

namespace hand {
namespace entry {
    auto init(const char* /* plugin_path */) -> bool { return true; }

    auto deinit(void) -> void { }

    auto get_factory(const char* factory_id) -> const void* {
        return (std::strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0) ? &hand::clap_factory
                                                                      : nullptr;
    }
} // namespace entry
} // namespace hand
