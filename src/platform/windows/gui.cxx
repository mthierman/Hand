#include <hand/helper.hxx>

namespace hand {
auto Helper::guiIsApiSupported(const char* api, bool isFloating) noexcept -> bool {
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

auto Helper::guiCreate(const char* /* api */, bool /* isFloating */) noexcept -> bool {
    // return gui.create();

    return false;
}

auto Helper::guiSetScale(double scale) noexcept -> bool {
    // return gui.setScale(scale);

    return false;
}

auto Helper::guiCanResize() const noexcept -> bool {
    // return true;

    return false;
}

auto Helper::guiAdjustSize(uint32_t* width, uint32_t* height) noexcept -> bool {
    // return guiSetSize(*width, *height);

    return false;
}

auto Helper::guiSetSize(uint32_t width, uint32_t height) noexcept -> bool {
    // return gui.setSize(width, height);

    return false;
}

auto Helper::guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool {
    // return gui.getSize(width, height);

    return false;
}

auto Helper::guiSetParent(const clap_window* window) noexcept -> bool {
    // return gui.setParent(window);

    return false;
}

auto Helper::guiShow() noexcept -> bool {
    // return gui.show();

    return false;
}

auto Helper::guiHide() noexcept -> bool {
    // return gui.hide();

    return false;
}

auto Helper::guiDestroy() noexcept -> void {
    // gui.destroy();
}

auto Helper::guiGetPreferredApi(const char** /* api */, bool* /* is_floating */) noexcept -> bool {
    return false;
}
} // namespace hand
