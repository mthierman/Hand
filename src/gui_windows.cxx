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

    Window m_window;

    auto init() -> bool {
        m_window.webViewEnvironment.m_userDataFolder
            = glow::filesystem::known_folder(FOLDERID_LocalAppData, { "template-clap-plugin" });

        return true;
    }

    auto create() -> bool {
        m_window.create();

        return true;
    }

    auto setScale(double scale) -> bool {
        m_window.m_scale = scale;

        return true;
    }

    auto setSize(uint32_t width, uint32_t height) -> bool {
        glow::window::set_position(m_window.m_hwnd.get(), 0, 0, width, height);

        return true;
    }

    auto getSize(uint32_t* width, uint32_t* height) -> bool {
        auto rect { glow::window::get_client_rect(m_window.m_hwnd.get()) };
        *width = rect.right - rect.left;
        *height = rect.bottom - rect.top;

        return true;
    }

    auto setParent(const clap_window* window) -> bool {
        glow::window::set_style(m_window.m_hwnd.get(), WS_POPUP);
        glow::window::set_parent(m_window.m_hwnd.get(), (::HWND)window->win32);

        return true;
    }

    auto show() -> bool {
        glow::window::show(m_window.m_hwnd.get());

        return true;
    }

    auto hide() -> bool {
        glow::window::hide(m_window.m_hwnd.get());

        return true;
    }

    auto destroy() -> void { m_window.close(); }
} // namespace gui
} // namespace hand
