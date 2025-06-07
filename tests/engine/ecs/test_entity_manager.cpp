#include <gtest/gtest.h>

#include <engine/ecs/entity_manager.hpp>
#include <iostream>

TEST(EntityManagerTest, CreateNewEntity) {
  EntityManager mg = EntityManager();
  Entity e = mg.createEntity(Signature(1));
  EXPECT_TRUE(e == 0);
}

TEST(EntityManagerTest, CreateNewEntityWithEmptySignature) {
  EntityManager mg = EntityManager();
  EXPECT_THROW({
    Entity e = mg.createEntity(Signature());
  }, std::invalid_argument);
}

TEST(EntityManagerTest, CreateMultipleNewEntities) {
  EntityManager mg = EntityManager();
  for (int i = 0; i != 5; ++i) {
    Entity e = mg.createEntity(Signature(1));
    EXPECT_TRUE(e == i);
  }
}

TEST(EntityManagerTest, AddSignatureToEntity) {
  EntityManager mg = EntityManager();
  Entity e = mg.createEntity(Signature(2));
  mg.setSignature(e, Signature(27));
  EXPECT_TRUE(Signature(27) == mg.getSignature(e));
}

TEST(EntityManagerTest, DeleteEntity) {
  EntityManager mg = EntityManager();
  Entity e = mg.createEntity(Signature(2));
  EXPECT_TRUE(Signature(2) == mg.getSignature(e));
  mg.deleteEntity(e);
  EXPECT_TRUE(Signature(0) == mg.getSignature(e));
}