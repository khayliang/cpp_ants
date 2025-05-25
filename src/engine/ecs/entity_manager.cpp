#include <stdexcept>

#include <engine/ecs/entity_manager.hpp>

Entity EntityManager::createEntity() {
  Entity entityToReturn;
  if (!freedEntities.empty()) {
    entityToReturn = freedEntities.front();
    freedEntities.pop();
  } else {
    if (createdEntities == MAX_ENTITIES)
      throw std::range_error("max entity limit reached");
    entityToReturn = createdEntities;
    createdEntities += 1;
  }
  return entityToReturn;
}

void EntityManager::deleteEntity(Entity entity) {
  if (signatures[entity].any()) {
    signatures[entity].reset();
    freedEntities.push(entity);
  } else {
    throw std::invalid_argument("entity not created");
  }
}