// clang-format off
#include <hand/descriptor.hxx>

namespace hand {
namespace descriptor {
    const char* id { "@PLUGIN_ID@" };
    const char* name { "@PLUGIN_NAME@" };
    const char* vendor { "@PLUGIN_VENDOR@" };
    const char* url { "@PLUGIN_URL@" };
    const char* manual_url { "@PLUGIN_MANUAL_URL@" };
    const char* support_url { "@PLUGIN_SUPPORT_URL@" };
    const char* version { "@PLUGIN_VERSION@" };
    const char* description { "@PLUGIN_DESCRIPTION@" };
    const std::array features { @PLUGIN_FEATURES@ };
} // namespace descriptor

const clap_plugin_descriptor clap_descriptor { .clap_version { CLAP_VERSION },
                                               .id { descriptor::id },
                                               .name { descriptor::name },
                                               .vendor { descriptor::vendor },
                                               .url { descriptor::url },
                                               .manual_url { descriptor::manual_url },
                                               .support_url { descriptor::support_url },
                                               .version { descriptor::version },
                                               .description { descriptor::description },
                                               .features { descriptor::features.data() } };
} // namespace hand
// clang-format on
