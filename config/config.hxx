// clang-format off
#include <array>

namespace plugin {
constexpr std::array features { @PLUGIN_FEATURES@, static_cast<const char*>(nullptr) };
} // namespace plugin
// clang-format on
