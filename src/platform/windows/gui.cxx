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
    webView.config.userDataFolder = glow::filesystem::known_folder() / L"template-clap-plugin";

    webView.background_style(glow::window::Background::Style::Transparent);

    webView.create([this]() {
    // webView.core->add_NavigationCompleted(
    //     webView.event.handler<ICoreWebView2NavigationCompletedEventHandler>(
    //         [this](ICoreWebView2* /* sender */,
    //                ICoreWebView2NavigationCompletedEventArgs* /* args */) {
    //     // webView.show();

    //     webView.show_controller();
    //     webView.put_bounds(webView.client_position());
    //     std::cout << "NavigationCompleted" << std::endl;

    //     return S_OK;
    // }),
    //     webView.event.token("NavigationCompleted"));

#if HOT_RELOAD
        webView.navigate(DEV_URL);
#else
        webView.navigate("http://localhost:5173/");
#endif
    }, false);

    webView.set_position(glow::window::Position(0, 0, 640, 480));

    return true;
}

auto Helper::guiSetScale(double scale) noexcept -> bool {
    // webView.scale = scale;

    return false;
}

auto Helper::guiCanResize() const noexcept -> bool { return true; }

auto Helper::guiAdjustSize(uint32_t* width, uint32_t* height) noexcept -> bool {
    return guiSetSize(*width, *height);
}

auto Helper::guiSetSize(uint32_t width, uint32_t height) noexcept -> bool {
    webView.set_position(
        glow::window::Position(0, 0, static_cast<int>(width), static_cast<int>(height)));

    return true;
}

auto Helper::guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool {
    auto position { webView.client_position() };

    *width = static_cast<uint32_t>(position.width);
    *height = static_cast<uint32_t>(position.height);

    return true;
}

auto Helper::guiSetParent(const clap_window* window) noexcept -> bool {
    webView.set_popup();
    webView.set_parent(static_cast<::HWND>(window->win32));

    return true;
}

auto Helper::guiShow() noexcept -> bool {
    webView.show();

    return true;
}

auto Helper::guiHide() noexcept -> bool {
    webView.hide();

    return true;
}

auto Helper::guiDestroy() noexcept -> void { webView.close(); }

auto Helper::guiGetPreferredApi(const char** /* api */, bool* /* is_floating */) noexcept -> bool {
    return false;
}
} // namespace hand
