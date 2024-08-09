#include <glow/filesystem.hxx>
#include <glow/system.hxx>
#include <glow/webview.hxx>
#include <glow/window.hxx>

namespace hand {
struct Window final : glow::window::Window {
    Window() {
        message(WM_CREATE, [this](glow::messages::wm_create /* message */) {
            glow::window::set_style(m_hwnd.get(), WS_POPUP);
            glow::window::set_position(m_hwnd.get(), 0, 0, 640, 480);

            webViewEnvironment.m_userDataFolder
                = glow::filesystem::known_folder(FOLDERID_LocalAppData, { "template-clap-plugin" });

            webViewEnvironment.create([this]() {
                webView.create(webViewEnvironment, m_hwnd.get(), [this]() {
#if HOT_RELOAD
                    webView.navigate(DEV_URL);
#else
                    webView.navigate("https://www.example.com/");
#endif
                    webView.put_bounds(m_hwnd.get());
                });
            });

            initialized = true;

            return 0;
        });

        message(WM_WINDOWPOSCHANGED, [this](glow::messages::wm_windowposchanged /* message */) {
            webView.put_bounds(m_hwnd.get());

            return 0;
        });
    }

    auto guiCreate() noexcept -> bool {
        if (!initialized) {
            create("WebView", false);
        }

        return true;
    }

    auto guiSetScale(double scale) noexcept -> bool {
        m_scale = scale;

        return true;
    }

    auto guiSetSize(uint32_t width, uint32_t height) noexcept -> bool {
        glow::window::set_position(
            m_hwnd.get(), 0, 0, static_cast<int>(width), static_cast<int>(height));

        return true;
    }

    auto guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool {
        auto rect { glow::window::get_client_rect(m_hwnd.get()) };

        *width = static_cast<uint32_t>(rect.right - rect.left);
        *height = static_cast<uint32_t>(rect.bottom - rect.top);

        return true;
    }

    auto guiSetParent(const clap_window* window) noexcept -> bool {
        glow::window::set_parent(m_hwnd.get(), static_cast<::HWND>(window->win32));
        glow::window::show(m_hwnd.get());
        webView.show();

        return true;
    }

    auto guiShow() noexcept -> bool {
        glow::window::show(m_hwnd.get());

        return true;
    }

    auto guiHide() noexcept -> bool {
        glow::window::hide(m_hwnd.get());

        return true;
    }

    auto destroy() noexcept -> void {
        webView.hide();
        glow::window::hide(m_hwnd.get());
        glow::window::set_parent(m_hwnd.get(), nullptr);
    }

    glow::webview::WebViewEnvironment webViewEnvironment;
    glow::webview::WebView webView;
    bool initialized { false };
};
} // namespace hand
