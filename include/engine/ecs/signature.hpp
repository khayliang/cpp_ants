#include <bitset>

#include "component.hpp"

// represents the components attached to an entity. LSB represents 
// if an entity is initialized or not
using Signature = std::bitset<MAX_COMPONENTS>;