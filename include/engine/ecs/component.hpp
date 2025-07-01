#include <cstdint>
#include "component_manager.hpp"

using ComponentType = std::uint8_t;

constexpr ComponentType MAX_COMPONENTS = 32;

template <typename T>
struct Component {
  private:
    bool registered = ()[] {
      continue;
    }();
}