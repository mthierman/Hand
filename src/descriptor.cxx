#include <plugin/features.hxx>
#include <plugin/descriptor.hxx>

namespace plugin {
const clap_plugin_descriptor clap_descriptor { .clap_version { CLAP_VERSION },
                                               .id { PLUGIN_ID },
                                               .name { PLUGIN_NAME },
                                               .vendor { PLUGIN_VENDOR },
                                               .url { PLUGIN_URL },
                                               .manual_url { PLUGIN_MANUAL_URL },
                                               .support_url { PLUGIN_SUPPORT_URL },
                                               .version { PLUGIN_VERSION },
                                               .description { PLUGIN_DESCRIPTION },
                                               .features { plugin::features.data() } };
} // namespace plugin
