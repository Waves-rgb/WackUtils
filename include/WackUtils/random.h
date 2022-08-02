#pragma once

#include <string>
#include <random>

namespace WackUtils::random {
	enum charSet {
		CS_ALPHA_LOWER 	= 0x0001,
		CS_ALPHA_UPPER 	= 0x0010,
		CS_ALPHA 		= CS_ALPHA_LOWER | CS_ALPHA_UPPER,
		CS_NUMERIC    	= 0x0100,
		CS_SPECIAL    	= 0x1000,
		CS_ALL         	= CS_ALPHA | CS_NUMERIC | CS_SPECIAL,
	};

	/// Generates a random string of the given length.
	/// @param length The length of the string to generate.
	/// @param charSet The character set to use.
	/// @returns The generated string.
	std::string getString(int length, const int strType = CS_ALL);

	/// Generates a random int between two given values.
	/// @param min The minimum value.
	/// @param max The maximum value.
	/// @returns The generated int.
	int get(int min, int max);

	/// Generates a random float between two given values.
	/// @param min The minimum value.
	/// @param max The maximum value.
	/// @returns The generated float.
	float get(float min, float max);

	/// Generates a random double between two given values.
	/// @param min The minimum value.
	/// @param max The maximum value.
	/// @returns The generated double.
	double get(double min, double max);

	/// Generates a random bool.
	/// @returns The generated bool.
	bool get();

	/// The random number generator
	std::default_random_engine generator;

	/// Method to seed the random number generator, for added security.
	/// @param seed The seed to use, if 0, the current time is used.
	/// @returns The seed used.
	void seed(unsigned int seed = 0);
}