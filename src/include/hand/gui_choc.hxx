#include <gui/choc_WebView.h>

namespace hand {
struct Window {
    auto guiCreate() noexcept -> bool {
        // ::SetEnvironmentVariable("WEBVIEW2_DEFAULT_BACKGROUND_COLOR", "0");
        choc::ui::WebView::Options options;
        options.transparentBackground = true;
        m_webview = std::make_unique<choc::ui::WebView>(options);
        m_webview->navigate("https://localhost:5173/");
        ::SetWindowPos((::HWND)m_webview->getViewHandle(),
                       nullptr,
                       0,
                       0,
                       200,
                       200,
                       SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE | SWP_FRAMECHANGED);

        return true;
    }

    auto guiSetScale(double scale) noexcept -> bool {
        //

        return true;
    }

    auto guiSetSize(uint32_t width, uint32_t height) noexcept -> bool {
        ::SetWindowPos((::HWND)m_webview->getViewHandle(),
                       nullptr,
                       0,
                       0,
                       width,
                       height,
                       SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE | SWP_FRAMECHANGED);

        return true;
    }

    auto guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool {
        *width = 200;
        *height = 200;

        return true;
    }

    auto guiSetParent(const clap_window* window) noexcept -> bool {
        ::SetWindowLongPtrW((::HWND)m_webview->getViewHandle(), GWL_STYLE, WS_CHILD);
        ::SetParent((::HWND)m_webview->getViewHandle(), (::HWND)window->win32);

        return true;
    }

    auto guiShow() noexcept -> bool {
        ::ShowWindow((::HWND)m_webview->getViewHandle(), SW_SHOW);

        return true;
    }

    auto guiHide() noexcept -> bool {
        ::ShowWindow((::HWND)m_webview->getViewHandle(), SW_HIDE);

        return true;
    }

    auto destroy() noexcept -> void { m_webview.reset(); }

    std::unique_ptr<choc::ui::WebView> m_webview;
};
} // namespace hand
