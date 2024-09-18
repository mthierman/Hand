#pragma once

#include <clap/helpers/plugin.hh>
#include <clap/helpers/plugin.hxx>

#include <cstring>
#include <memory>
#include <unordered_map>

#include "descriptor.hxx"

#if defined(PLATFORM_WINDOWS)
#include <glow/glow.hxx>
#endif

namespace hand {
struct Helper : public clap::helpers::Plugin<clap::helpers::MisbehaviourHandler::Terminate,
                                             clap::helpers::CheckingLevel::Maximal> {
    Helper(const clap_host* host);

    auto paramsCount() const noexcept -> uint32_t override;

    // gui
    auto guiIsApiSupported(const char* api, bool isFloating) noexcept -> bool override;
    auto guiCreate(const char* /* api */, bool /* isFloating */) noexcept -> bool override;
    auto guiSetScale(double scale) noexcept -> bool override;
    auto guiCanResize() const noexcept -> bool override;
    auto guiAdjustSize(uint32_t* width, uint32_t* height) noexcept -> bool override;
    auto guiSetSize(uint32_t width, uint32_t height) noexcept -> bool override;
    auto guiGetSize(uint32_t* width, uint32_t* height) noexcept -> bool override;
    auto guiSetParent(const clap_window* window) noexcept -> bool override;
    auto guiShow() noexcept -> bool override;
    auto guiHide() noexcept -> bool override;
    auto guiDestroy() noexcept -> void override;
    auto guiGetPreferredApi(const char** /* api */,
                            bool* /* is_floating */) noexcept -> bool override;

    // audio ports
    auto audioPortsCount(bool /* isInput */) const noexcept -> uint32_t override;
    auto audioPortsInfo(uint32_t index,
                        bool /* isInput */,
                        clap_audio_port_info* info) const noexcept -> bool override;

    // note ports
    auto notePortsCount(bool /* isInput */) const noexcept -> uint32_t override;
    auto notePortsInfo(uint32_t index,
                       bool /* isInput */,
                       clap_note_port_info* info) const noexcept -> bool override;

#if defined(PLATFORM_WINDOWS)
    glow::window::WebView webView;
    ::HHOOK hook;

    static auto CALLBACK call_window_procedure(int code,
                                               ::WPARAM wparam,
                                               ::LPARAM lparam) -> ::LRESULT;
#endif
    std::unordered_map<clap_id, double*> params;
};
} // namespace hand
