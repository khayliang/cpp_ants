#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "engine/ecs/component_manager.hpp"

struct comp { int val; };
struct comp1 {int val; };
struct comp2 {int val; };



TEST(ComponentManagerTest, RegisterComponent) {
  ComponentManager manager;
  manager.registerComponent<comp>();
  manager.registerComponent<comp1>();
  manager.registerComponent<comp2>();


  ASSERT_TRUE(manager.getComponentType<comp>() == 0);
  ASSERT_TRUE(manager.getComponentType<comp1>() == 1);
  ASSERT_TRUE(manager.getComponentType<comp2>() == 2);
}

TEST(ComponentManagerTest, AddComponent) {
  ComponentManager manager;
  manager.registerComponent<comp>();
  manager.registerComponent<comp1>();
  manager.registerComponent<comp2>();

  Entity e = 1;
  comp compval = comp { 3 };
  manager.addComponent<comp>(e, compval);
  ASSERT_TRUE(manager.getComponent<comp>(e).val == 3);
}
