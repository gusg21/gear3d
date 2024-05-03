//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_SYSTEMMANAGER_H
#define GEAR3D_SYSTEMMANAGER_H

#include <unordered_map>
#include <typeinfo>

#include "entity.h"
#include "system.h"

namespace g3d {
    class SystemManager {
    public:
        SystemManager() = default;
        SystemManager(const SystemManager&) = delete;
        SystemManager& operator=(const SystemManager&) = delete;

        template<typename T>
        T* RegisterSystem();

        template<typename T>
        void SetSignature(EntitySignature signature);

        void EntityDestroyed(EntityId entity);

        void EntitySignatureChanged(EntityId entity, EntitySignature entitySignature);

    private:
        std::unordered_map<const char*, EntitySignature> m_Signatures { };
        std::unordered_map<const char*, System*> m_Systems { };
    };

    template<typename T>
    T* SystemManager::RegisterSystem() {
        const char* typeName = typeid(T).name();

        T* system = new T();
        m_Systems.insert({ typeName, system });

        return system;
    }

    template<typename T>
    void SystemManager::SetSignature(EntitySignature signature) {
        const char* typeName = typeid(T).name();

        m_Signatures.insert({typeName, signature});
    }
}

#endif //GEAR3D_SYSTEMMANAGER_H
