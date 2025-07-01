#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "engine/ecs/component_manager.hpp"

TEST(ComponentManagerTest, AddAndGetData) {
  ComponentManager manager;
  manager.addComponent<Component>(Entity e, Component comp);
  manager.getComponent<Component>(Entity e);
}
