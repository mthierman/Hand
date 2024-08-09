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

    auto setParent(const clap_window* window) -> void {
        glow::window::set_parent(m_hwnd.get(), static_cast<::HWND>(window->win32));
        glow::window::show(m_hwnd.get());
        webView.show();
    }

    auto destroy() -> void {
        webView.hide();
        glow::window::hide(m_hwnd.get());
        glow::window::set_parent(m_hwnd.get(), nullptr);
    }

    glow::webview::WebViewEnvironment webViewEnvironment;
    glow::webview::WebView webView;
    bool initialized { false };
};
} // namespace hand
