#include <glow/filesystem.hxx>
#include <glow/system.hxx>
#include <glow/webview.hxx>
#include <glow/window.hxx>

namespace hand {
struct Window final : glow::window::Window {
    Window() {
        webViewEnvironment.m_userDataFolder
            = glow::filesystem::known_folder(FOLDERID_LocalAppData, { "template-clap-plugin" });

        message(WM_CREATE, [this](glow::messages::wm_create /* message */) {
            glow::window::set_position(m_hwnd.get(), 0, 0, 640, 480);

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

            return 0;
        });

        message(WM_WINDOWPOSCHANGED, [this](glow::messages::wm_windowposchanged /* message */) {
            webView.put_bounds(m_hwnd.get());

            return 0;
        });

        message(WM_DESTROY, [this](glow::messages::wm /* message */) {
            webView.close();
            webViewEnvironment.close();

            return 0;
        });
    }

    glow::webview::WebViewEnvironment webViewEnvironment;
    glow::webview::WebView webView;
};
} // namespace hand
