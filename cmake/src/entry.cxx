#include <hand/entry.hxx>

extern "C" {
const CLAP_EXPORT clap_plugin_entry clap_entry { .clap_version { CLAP_VERSION },
                                                 .init { hand::entry::init },
                                                 .deinit { hand::entry::deinit },
                                                 .get_factory { hand::entry::get_factory } };
}
