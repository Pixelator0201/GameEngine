#pragma once

#include "Transform.h"
#include "Model.h"
#include <string>

namespace nu
{
    class Scene;

    struct ActorDesc
    {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity{ 0.0f, 0.0f };
        Model model;
    };

    class Actor
    {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_name{ actorDesc.name },
            m_tag{ actorDesc.tag },
            m_transform{ actorDesc.transform },
            m_velocity{ actorDesc.velocity },
            m_model{ actorDesc.model }
        { }

        Actor(const Transform& transform) : m_transform{ transform } {}
        Actor(const Transform& transform, const Model& model) :
            m_transform{ transform },
            m_model{ model }
        { }

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        const Transform& GetTransform() const { return m_transform; }
        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(const float rotation) { m_transform.rotation = rotation; }
        void SetScale(const float scale) { m_transform.scale = scale; }

        const Vector2 GetVelocity() const { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }

        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }

        Scene* GetScene() { return m_scene; }

        friend Scene;

    protected:
        std::string m_name;
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };

        Model m_model;
        Scene* m_scene{ nullptr };
    };

}