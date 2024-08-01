#include <plugin/entry.hxx>

extern "C" {
const CLAP_EXPORT clap_plugin_entry clap_entry { .clap_version { CLAP_VERSION },
                                                 .init { plugin::entry::init },
                                                 .deinit { plugin::entry::deinit },
                                                 .get_factory { plugin::entry::get_factory } };
}
