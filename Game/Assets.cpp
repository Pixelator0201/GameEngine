#include "Assets.h"

using namespace nu;
namespace assets
{
	Mesh playerMesh{ { Vector2{ 2, 0 }, Vector2{ -2, 2 }, Vector2{ -1, 0 }, Vector2{-2, -2}, Vector2{2, 0} }, Color{ 0.0f, 0.0f, 1.0f } };
	Mesh playerMesh2{ { Vector2{ 0, 1 }, Vector2{ -3, 5 }, Vector2{ 2, 0 }, Vector2{ -3, -5 }, Vector2{ 0, -1 } }, Color{ 255, 255, 0 } };
	Model playerModel{ std::vector<Mesh>{ playerMesh, playerMesh2 } };

	Mesh enemyMesh{ { Vector2{ 2, 0 }, Vector2{ -2, 2 }, Vector2{ -1, 0 }, Vector2{-2, -2}, Vector2{2, 0} }, Color{ 1.0f, 0.0f, 0.0f } };
	Mesh enemyMesh2{ { Vector2{ 0, 1 }, Vector2{ -3, 5 }, Vector2{ 2, 0 }, Vector2{ -3, -5 }, Vector2{ 0, -1 } }, Color{ 255, 255, 0 } };
	Model enemyModel{ std::vector<Mesh>{ enemyMesh, enemyMesh2 } };

	Mesh bulletMesh{
    {
		Vector2{ -1, -1 },
		Vector2{ 1, 0 },
		Vector2{ -1, 1 },
		Vector2{ -1, -1 },
	},
		Color{ 1.0f, 0.0f, 0.0f }
	};
	Model bulletModel{ std::vector<Mesh>{ bulletMesh } };
}