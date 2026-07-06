#pragma once

#include <cstdlib>

namespace nu
{
	inline int RandomInt()
	{
		return rand();
	}

	/// <summary>
	/// Get random integer value [0, max)
	/// </summary>
	/// <param name="max">exclusive maximum</param>
	/// <returns>Random number between 0 and max (exclusive)</returns>
	inline int RandomInt(int max) 
	{
		return rand() % max;
	}
	/// <summary>
	/// Get random integer value [min, max]
	/// </summary>
	/// <param name="min">inclusive minimum</param>
	/// <param name="max">inclusive maximum</param>
	/// <returns>Random number between min and max (inclusive)</returns>
	inline int RandomInt(int min, int max)
	{
		return min + (rand() % max - min + 1);
	}

	inline float RandomFloat()
	{
		// rand() = 0 <- RAND_MAX
		return rand() / (float)RAND_MAX;
	}

	inline float RandomFloat(float max)
	{
		return RandomFloat() * max;
	}

	inline float RandomFloat(float min, float max)
	{
		return min + RandomFloat() * (max - min);
	}
}