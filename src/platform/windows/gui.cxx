#include <hand/helper.hxx>

namespace hand {
auto Helper::guiIsApiSupported(const char* api, bool isFloating) noexcept -> bool override {
    if (isFloating) {
        return false;
    }

    if (PLATFORM_WINDOWS) {
        if (std::strcmp(api, CLAP_WINDOW_API_WIN32) == 0) {
            return true;
        }
    }

    return false;
}

auto Helper::guiCreate(const char* /* api */, bool /* isFloating */) noexcept -> bool override {
    return gui.create();
}

auto Helper::guiSetScale(double scale) noexcept -> bool override { return gui.setScale(scale); }

auto Helper::guiCanResize() const noexcept -> bool override { return true; }

auto Helper::guiAdjustSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
    return guiSetSize(*width, *height);
}

auto Helper::guiSetSize(uint32_t width, uint32_t height) noexcept -> bool override {
    return gui.setSize(width, height);
}

auto Helper::guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool override {
    return gui.getSize(width, height);
}

auto Helper::guiSetParent(const clap_window* window) noexcept -> bool override {
    return gui.setParent(window);
}

auto Helper::guiShow() noexcept -> bool override { return gui.show(); }

auto Helper::guiHide() noexcept -> bool override { return gui.hide(); }

auto Helper::guiDestroy() noexcept -> void override { gui.destroy(); }

auto Helper::guiGetPreferredApi(const char** /* api */,
                                bool* /* is_floating */) noexcept -> bool override {
    return false;
}
} // namespace hand
