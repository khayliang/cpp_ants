#include <cstdint>
using Entity = std::uint32_t;

#ifdef TESTING
constexpr Entity MAX_ENTITIES = 20;
#else
constexpr Entity MAX_ENTITIES = 10000;
#endif