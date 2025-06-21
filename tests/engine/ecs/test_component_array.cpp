#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "engine/ecs/component_array.hpp"

TEST(ComponentArrayTest, AddAndGetData) {
  ComponentArray<int> arr;
  Entity e1 = 1;
  int e1data = 3;
  Entity e2 = 4;
  int e2data = 4;
  arr.insertData(e1, e1data);
  arr.insertData(e2, e2data);
  EXPECT_TRUE(arr.getData(e1) == e1data);
  EXPECT_TRUE(arr.getData(e2) == e2data);
}

TEST(ComponentArrayTest, DeleteDataForEntity) {
  ComponentArray<int> arr;
  Entity e1 = 1;
  int e1data = 3;
  Entity e2 = 4;
  int e2data = 4;
  arr.insertData(e1, e1data);
  arr.insertData(e2, e2data);
  EXPECT_TRUE(arr.getData(e1) == e1data);
  EXPECT_TRUE(arr.getData(e2) == e2data);
  arr.deleteEntity(e1);
  arr.deleteEntity(e2);
  EXPECT_THROW(arr.getData(e1), std::out_of_range);
  EXPECT_THROW(arr.getData(e2), std::out_of_range);
}

TEST(ComponentArrayTest, UpsertAndUpdataDataForEntity) {
  ComponentArray<int> arr;
  Entity e1 = 1;
  int e1data = 3;
  int e2data = 4;
  arr.insertData(e1, e1data);
  EXPECT_TRUE(arr.getData(e1) == e1data);
  arr.updateData(e1, e2data);
  EXPECT_TRUE(arr.getData(e1) == e2data);
  arr.upsertData(e1, e1data);
  EXPECT_TRUE(arr.getData(e1) == e1data);
}