#ifndef ENTITY_MANAGER_HPP_INCLUDED
#define ENTITY_MANAGER_HPP_INCLUDED

#include <unordered_map>
#include <memory>
#include <cstdint>

#include "Entity.hpp"
#include "Vector.hpp"

namespace Game {

    class EntityManager {
        std::unordered_map<uint16_t, std::unique_ptr<Entity>> entities;

        uint16_t last_id = 0;

        uint16_t getFreeId() {
            uint16_t start_id = last_id;

            while (!isIdFree(++last_id)) {
                if (last_id == start_id) {
                    return 0;
                }
            }

            return last_id;
        }

        bool isIdFree(uint16_t id) {
            if (id == 0) {
                return false;
            }

            return entities.find(id) == entities.end();
        }

    public:
        uint16_t addEntity(std::unique_ptr<Entity> entity) {
            uint16_t id = getFreeId();

            if (id == 0) {
                return 0;
            }

            entity->setId(id);

            entities[id] = std::move(entity);

            return id;
        }

        Entity *getEntity(uint16_t id) {
            // If id == 0 or it is not used, then there is no entity with that id
            if (isIdFree(id)) {
                return nullptr;
            }

            return entities[id].get();
        }

        void delEntity(uint16_t id) {
            if (!isIdFree(id)) {
                entities.erase(id);
            }
        }

        void update(GameState &game) {
            for (auto iter = entities.begin(); iter != entities.end(); ++iter) {
                iter->second->update(game);
            }
        }

        void render(Display &d, Vector2i cam) {
            for (auto iter = entities.begin(); iter != entities.end(); ++iter) {
                iter->second->render(d, cam);
            }
        }

    };
}

#endif
