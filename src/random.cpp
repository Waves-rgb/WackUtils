#include <WackUtils/random.h>
#include <map>

std::map<WackUtils::random::charSet, std::string> csData = {
		{WackUtils::random::CS_ALPHA_LOWER, "abcdefghijklmnopqrstuvwxyz"},
		{WackUtils::random::CS_ALPHA_UPPER, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
		{WackUtils::random::CS_NUMERIC, "0123456789"},
		{WackUtils::random::CS_SPECIAL, "!@#$%^&*()_+-=[]{}|;':,./<>?"}
};

std::string WackUtils::random::getString(int length, const int strType) {
	std::string str, cs;
	for (auto &c : csData) if (strType & c.first) cs += c.second;
	for (int i = 0; i < length; i++) str += cs[get(0, cs.length() - 1)];
	return str;
}

int WackUtils::random::get(int min, int max) {
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

float WackUtils::random::get(float min, float max) {
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}

double WackUtils::random::get(double min, double max) {
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}

bool WackUtils::random::get() {
	return get(0, 1) == 1;
}

void WackUtils::random::seed(unsigned int seed) {
	if (seed == 0) seed = time(nullptr);
	generator.seed(seed);
}
