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
    if (entityToIdxMapping_.end() == entityToIdxMapping_.find(e)) {
      throw std::out_of_range("Entity does not exist. Nothing to read");
    }
    size_t idx = entityToIdxMapping_[e];
    return componentArray_[idx];
  }

  void insertData(Entity e, const T& data) {
    if (entityToIdxMapping_.find(e) != entityToIdxMapping_.end()) {
      throw std::out_of_range("Entity already exists. Unable to insert");
    }

    if (size_ == MAX_ENTITIES)
      throw std::out_of_range(
          "Max number of entities reached. Unable to insert entity");
    entityToIdxMapping_[e] = size_;
    idxToEntityMapping_[size_] = e;
    componentArray_[size_] = data;
    ++size_;
  }

  void updateData(Entity e, const T& data) {
    if (entityToIdxMapping_.end() == entityToIdxMapping_.find(e)) {
      throw std::out_of_range("Entity does not exist. Unable to update");
    }

    size_t idx = entityToIdxMapping_[e];
    componentArray_[idx] = data;
  }

  void upsertData(Entity e, const T& data) {
    if (entityToIdxMapping_.find(e) != entityToIdxMapping_.end())
      updateData(e, data);
    else
      insertData(e, data);
  }

  void deleteEntity(Entity e) override {
    if (entityToIdxMapping_.end() == entityToIdxMapping_.find(e)) {
      throw std::out_of_range("Entity does not exist. Unable to delete");
    }
    size_t idxToRemove = entityToIdxMapping_[e];
    size_t idxLastElem = size_ - 1;

    if (idxToRemove == idxLastElem) {
      entityToIdxMapping_.erase(e);
      idxToEntityMapping_.erase(e);
      --size_;
      return;
    }

    Entity entityToMove = idxToEntityMapping_[idxLastElem];

    componentArray_[idxToRemove] = std::move(componentArray_[idxLastElem]);
    entityToIdxMapping_.erase(e);
    entityToIdxMapping_[entityToMove] = idxToRemove;
    idxToEntityMapping_[idxToRemove] = entityToMove;
    --size_;
  };

 private:
  size_t size_ = 0;
  std::array<T, MAX_ENTITIES> componentArray_{};
  std::unordered_map<Entity, size_t> entityToIdxMapping_{};
  std::unordered_map<size_t, Entity> idxToEntityMapping_{};
};
