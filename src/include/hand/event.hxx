#pragma once

#include <clap/events.h>
#include <clap/process.h>

#include <functional>

namespace hand::event {
auto run_loop(const clap_process* process,
              std::function<void(const clap_event_header* event)> eventHandler)
    -> clap_process_status;
} // namespace hand::event
