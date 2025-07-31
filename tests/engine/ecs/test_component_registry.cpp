#include <gtest/gtest.h>

#include "engine/ecs/component_registry.hpp"

struct comp1 {};
struct comp2 {};
struct comp3 {};

struct comp4 {};

using TestRegistry = ComponentRegistryBase<comp1, comp2, comp3>;

TEST(ComponentRegistryTest, GetNumberOfComponents) {
  EXPECT_TRUE(TestRegistry::totalComponents == 3);
}

TEST(ComponentRegistryTest, GetIDOfComponents) {
  EXPECT_TRUE(TestRegistry::index<comp1> == 0);
  EXPECT_TRUE(TestRegistry::index<comp2> == 1);
  EXPECT_TRUE(TestRegistry::index<comp3> == 2);
}

