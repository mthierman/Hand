#include <hand/gui.hxx>

namespace hand {
namespace gui {
    auto init() -> bool { return false; }
    auto create() -> bool { return false; }
    auto setScale(double /* scale */) -> bool { return false; }
    auto setSize(uint32_t /* width */, uint32_t /* height */) -> bool { return false; }
    auto getSize(uint32_t* /* width */, uint32_t* /* height */) -> bool { return false; }
    auto setParent(const clap_window* /* window */) -> bool { return false; }
    auto show() -> bool { return false; }
    auto hide() -> bool { return false; }
    auto destroy() -> void { }
} // namespace gui
} // namespace hand
