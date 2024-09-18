#include <glow/filesystem.hxx>
#include <glow/system.hxx>
#include <glow/window.hxx>

namespace hand {
::HWND messageHwnd;

struct GUI {
    struct WebView final : glow::window::WebView {
        WebView() {
            config.userDataFolder = glow::filesystem::known_folder() / L"template-clap-plugin";

            create([this]() {
            //
#if HOT_RELOAD
                navigate(DEV_URL);
#else
                navigate("https://www.example.com/");
#endif
            });

            set_position(glow::window::Position(0, 0, 640, 480));

            messageHwnd = hwnd.get();

            hook = ::SetWindowsHookExW(WH_CALLWNDPROC,
                                       call_window_procedure,
                                       glow::system::instance(),
                                       ::GetCurrentThreadId());
        }

        ~WebView() { ::UnhookWindowsHookEx(hook); }

        ::HHOOK hook;

        static auto CALLBACK call_window_procedure(int code,
                                                   ::WPARAM wparam,
                                                   ::LPARAM lparam) -> ::LRESULT {
            auto cwp { reinterpret_cast<::CWPSTRUCT*>(lparam) };

            if (code < 0) {
                return ::CallNextHookEx(nullptr, code, wparam, lparam);
            } else {
                if (cwp && cwp->message == WM_SETTINGCHANGE
                    && ::CompareStringOrdinal(reinterpret_cast<wchar_t*>(cwp->lParam),
                                              -1,
                                              L"ImmersiveColorSet",
                                              -1,
                                              true)) {
                    std::cout << "WM_SETTINGCHANGE: "
                              << glow::text::to_string((wchar_t*)cwp->lParam) << std::endl;
                    ::SendMessageW(messageHwnd, WM_SETTINGCHANGE, 0, 0);
                }

                return ::CallNextHookEx(nullptr, code, wparam, lparam);
            }
        }
    };

    auto create() noexcept -> bool {
        webView = std::make_unique<WebView>();

        return true;
    }

    auto setScale(double scale) noexcept -> bool {
        // webView->scale = scale;

        return false;
    }

    auto setSize(uint32_t width, uint32_t height) noexcept -> bool {
        webView->set_position(
            glow::window::Position(0, 0, static_cast<int>(width), static_cast<int>(height)));

        return true;
    }

    auto getSize(uint32_t* width, uint32_t* height) noexcept -> bool {
        auto position { webView->client_position() };

        *width = static_cast<uint32_t>(position.width);
        *height = static_cast<uint32_t>(position.height);

        return true;
    }

    auto setParent(const clap_window* window) noexcept -> bool {
        webView->set_popup();
        webView->set_parent(static_cast<::HWND>(window->win32));

        return true;
    }

    auto show() noexcept -> bool {
        webView->show();

        return true;
    }

    auto hide() noexcept -> bool {
        webView->hide();

        return true;
    }

    auto destroy() noexcept -> void { webView->hwnd.reset(); }

    std::unique_ptr<WebView> webView;
};
} // namespace hand