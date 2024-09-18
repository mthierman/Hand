// clang-format off
#include <hand/descriptor.hxx>

namespace hand::descriptor {
const char* id { "@PLUGIN_ID@" };
const char* name { "@PLUGIN_NAME@" };
const char* vendor { "@PLUGIN_VENDOR@" };
const char* url { "@PLUGIN_URL@" };
const char* manual_url { "@PLUGIN_MANUAL_URL@" };
const char* support_url { "@PLUGIN_SUPPORT_URL@" };
const char* version { "@PLUGIN_VERSION@" };
const char* description { "@PLUGIN_DESCRIPTION@" };
const std::vector<const char*> features { @PLUGIN_FEATURES@ };
const clap_plugin_descriptor clap_descriptor { .clap_version { CLAP_VERSION },
                                               .id { id },
                                               .name { name },
                                               .vendor { vendor },
                                               .url { url },
                                               .manual_url { manual_url },
                                               .support_url { support_url },
                                               .version { version },
                                               .description { description },
                                               .features { features.data() } };
} // namespace hand::descriptor
// clang-format on
