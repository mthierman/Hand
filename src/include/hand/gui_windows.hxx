#include <glow/filesystem.hxx>
#include <glow/system.hxx>
#include <glow/window.hxx>

namespace hand {
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
