#include <type_traits>

#include "component.hpp"

template<typename T, typename... Rest>
struct IndexOf;

template<typename T, typename... Rest>
struct IndexOf<T, T, Rest...> {
    static constexpr ComponentType value = 0;
};

template<typename T, typename U, typename... Rest>
struct IndexOf<T, U, Rest...> {
    static constexpr ComponentType value = 1 + IndexOf<T, Rest...>::value;
};

template<typename T>
struct IndexOf<T> {
    static_assert([] { return false; }(), "Component type not found");
};

template<typename... Types>
class ComponentRegistryBase {
  public:
    static constexpr ComponentType totalComponents = sizeof...(Types);

    template <typename T>
    static constexpr ComponentType index = IndexOf<T, Types...>::value;
};

