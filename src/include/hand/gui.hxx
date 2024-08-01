#pragma once

#include <clap/ext/gui.h>

namespace hand {
namespace gui {
    auto create() -> bool;
    auto setScale(double scale) -> bool;
    auto setSize(uint32_t width, uint32_t height) -> bool;
    auto getSize(uint32_t* width, uint32_t* height) -> bool;
    auto setParent(const clap_window* window) -> bool;
    auto show() -> bool;
    auto hide() -> bool;
    auto destroy() -> void;
} // namespace gui
} // namespace hand
