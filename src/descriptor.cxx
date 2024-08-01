#include <hand/descriptor.hxx>

namespace hand {
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
