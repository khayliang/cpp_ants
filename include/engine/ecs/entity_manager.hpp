#include <array>
#include <queue>

#include "entity.hpp"
#include "signature.hpp"

class EntityManager {
 public:
  Entity createEntity(Signature);
  void deleteEntity(Entity);
  void setSignature(Entity, Signature);
  Signature getSignature(Entity);

 private:
  std::array<Signature, MAX_ENTITIES> signatures;
  std::queue<Entity> freedEntities;
  Entity createdEntities = 0;
};