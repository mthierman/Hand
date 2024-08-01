#pragma once

#include <clap/all.h>

#include <functional>

namespace plugin {
namespace event {
    auto run_loop(const clap_process* process,
                  std::function<void(const clap_event_header* event)> eventHandler)
        -> clap_process_status;
} // namespace event
} // namespace plugin
