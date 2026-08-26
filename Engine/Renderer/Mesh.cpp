#include "pch.h"
#include "Mesh.h"

namespace nu
{
    float Mesh::GetRadius() const
    {
        float radius = 0.0f;
        
        for (const auto& point : m_points)
        {
            // get mesh radius
            float length = point.Length();
            // if radius is larger than current radius, radius is new radius (what?)
            if (length > radius)
                radius = length;
        }

        return radius;
    }
}