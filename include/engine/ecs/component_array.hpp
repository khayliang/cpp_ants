#include <array>
#include <cstddef>
#include <unordered_map>

#include "entity.hpp"

class IComponentArray {
 public:
  virtual ~IComponentArray() = default;
  virtual void deleteEntity(Entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
 public:
  const T& getData(Entity e) {
    if (entityToIdxMapping.end() == entityToIdxMapping.find(e)) {
      throw std::out_of_range("Entity does not exist. Nothing to read");
    }
    size_t idx = entityToIdxMapping[e];
    return componentArray[idx];
  }

  void insertData(Entity e, const T& data) {
    if (entityToIdxMapping.find(e) != entityToIdxMapping.end()) {
      throw std::out_of_range("Entity already exists. Unable to insert");
    }

    if (size == MAX_ENTITIES)
      throw std::out_of_range(
          "Max number of entities reached. Unable to insert entity");
    entityToIdxMapping[e] = size;
    idxToEntityMapping[size] = e;
    componentArray[size] = data;
    ++size;
  }

  void updateData(Entity e, const T& data) {
    if (entityToIdxMapping.end() == entityToIdxMapping.find(e)) {
      throw std::out_of_range("Entity does not exist. Unable to update");
    }

    size_t idx = entityToIdxMapping[e];
    componentArray[idx] = data;
  }

  void upsertData(Entity e, const T& data) {
    if (entityToIdxMapping.find(e) != entityToIdxMapping.end())
      updateData(e, data);
    else
      insertData(e, data);
  }

  void deleteEntity(Entity e) override {
    if (entityToIdxMapping.end() == entityToIdxMapping.find(e)) {
      throw std::out_of_range("Entity does not exist. Unable to delete");
    }
    size_t idxToRemove = entityToIdxMapping[e];
    size_t idxLastElem = size - 1;

    if (idxToRemove == idxLastElem) {
      entityToIdxMapping.erase(e);
      idxToEntityMapping.erase(e);
      --size;
      return;
    }

    Entity entityToMove = idxToEntityMapping[idxLastElem];

    componentArray[idxToRemove] = std::move(componentArray[idxLastElem]);
    entityToIdxMapping.erase(e);
    entityToIdxMapping[entityToMove] = idxToRemove;
    idxToEntityMapping[idxToRemove] = entityToMove;
    --size;
  };

 private:
  size_t size = 0;
  std::array<T, MAX_ENTITIES> componentArray{};
  std::unordered_map<Entity, size_t> entityToIdxMapping{};
  std::unordered_map<size_t, Entity> idxToEntityMapping{};
};
