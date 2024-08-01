#include "hand/gui.hxx"

namespace hand {
namespace gui {
    auto create() -> bool { return true; }
    auto setScale(double scale) -> bool { return true; }
    auto setSize(uint32_t width, uint32_t height) -> bool { return true; }
    auto getSize(uint32_t width, uint32_t height) -> bool { return true; }
    auto setParent(const clap_window* window) -> bool { return true; }
    auto show() -> bool { return true; }
    auto hide() -> bool { return true; }
    auto destroy() -> void { }
} // namespace gui
} // namespace hand
