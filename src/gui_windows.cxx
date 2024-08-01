#include "hand/gui.hxx"

#include <glow/filesystem.hxx>
#include <glow/system.hxx>
#include <glow/webview.hxx>
#include <glow/window.hxx>

namespace hand {
namespace gui {
    struct Window final : glow::window::Window {
        Window() {
            message(WM_CREATE, [this](glow::messages::wm_create /* message */) {
                glow::window::set_position(m_hwnd.get(), 0, 0, 640, 480);

                if (!webViewEnvironment.m_environment) {
                    webViewEnvironment.create([this]() { createWebView(); });
                } else {
                    createWebView();
                }

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

        auto createWebView() -> void {
            webView.create(webViewEnvironment, m_hwnd.get(), [this]() {
#if HOT_RELOAD
                webView.navigate(DEV_URL);
#else
                webView.navigate("https://www.example.com/");
#endif
                webView.put_bounds(m_hwnd.get());
            });
        }

        glow::webview::WebViewEnvironment webViewEnvironment;
        glow::webview::WebView webView;
    };

    auto create() -> bool { return true; }
    auto setScale(double scale) -> bool { return true; }
    auto setSize(uint32_t width, uint32_t height) -> bool { return true; }
    auto getSize(uint32_t* width, uint32_t* height) -> bool { return true; }
    auto setParent(const clap_window* window) -> bool { return true; }
    auto show() -> bool { return true; }
    auto hide() -> bool { return true; }
    auto destroy() -> void { }
} // namespace gui
} // namespace hand
