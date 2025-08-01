#include <type_traits>
#include <unordered_map>
#include <array>
#include <cstddef>
#include <typeindex>
#include <stdexcept>
#include <memory>

#include "component_array.hpp"
#include "component.hpp"

class ComponentManager {
  public:
    template <typename T>
    void registerComponent() {
      if (componentTypeMap_.find(typeid(T)) != componentTypeMap_.end()) {
        throw std::invalid_argument("Component already registered");
      }
      if (registeredComponentCnt_ >= MAX_COMPONENTS) {
        throw std::length_error("Maximum amount of components registered");
      }
      ComponentType newType = registeredComponentCnt_;
      ++registeredComponentCnt_;
      componentTypeMap_[typeid(T)] = newType;
      componentArrayMap_[newType] = std::make_shared<ComponentArray<T>>();
    }

    template <typename T>
    ComponentType getComponentType() {
      if (componentTypeMap_.find(typeid(T)) == componentTypeMap_.end()) {
        throw std::invalid_argument("Component not registered");
      };
      return componentTypeMap_[typeid(T)];
    }

    template <typename T>
    void addComponent(Entity entity, T component) {
      getComponentArray<T>()->insertData(entity, component);
    }

    template <typename T>
    void removeComponent(Entity entity) {
      getComponentArray<T>()->removeData(entity);
    }

    template <typename T>
    T& getComponent(Entity entity) {
      return getComponentArray<T>()->getData(entity);
    }

  private:
    ComponentType registeredComponentCnt_ = 0;
    std::unordered_map<std::type_index, ComponentType> componentTypeMap_ {};
    std::unordered_map<ComponentType, std::shared_ptr<IComponentArray>> componentArrayMap_ {};

    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
      ComponentType typ = getComponentType<T>();
      std::shared_ptr<IComponentArray> arrPtr = componentArrayMap_[typ];

      return std::static_pointer_cast<ComponentArray<T>>(arrPtr);
    }
};

