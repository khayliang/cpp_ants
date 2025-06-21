#include <iostream>
#include <stdexcept>

#include "engine/ecs/entity_manager.hpp"

Entity EntityManager::createEntity(Signature sig) {
  if (sig.none()) throw std::invalid_argument("signature cannot be empty");
  
  Entity entityToReturn;
  if (!freedEntities.empty()) {
    entityToReturn = freedEntities.front();
    freedEntities.pop();
  } else {
    if (createdEntities == MAX_ENTITIES)
      throw std::out_of_range("max entity limit reached");
    entityToReturn = createdEntities;
    createdEntities += 1;
  }
  signatures[entityToReturn] = sig;
  return entityToReturn;
}

void EntityManager::setSignature(Entity entity, Signature sig) {
  if (sig.none()) throw std::invalid_argument("signature cannot be empty");
  signatures[entity] = sig;
}

Signature EntityManager::getSignature(Entity entity) {
  return signatures[entity];
}

void EntityManager::deleteEntity(Entity entity) {
  if (entity >= createdEntities || signatures[entity].none())
    throw std::invalid_argument("entity not created");

  signatures[entity].reset();
  freedEntities.push(entity);
}