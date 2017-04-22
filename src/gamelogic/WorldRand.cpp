#include "WorldRand"

WorldRand::WorldRand() {
}

float WorldRand::getRandRad(float min, float max) {
	distRad = uniform_real_distribution(min, max);
	return distRad(generator);
}

float WorldRand::getRandHeight(float min, float max) {
	distHeight = uniform_real_distribution(min, max);
	return distHeight(generator);
}

unsigned int WorldRand::getRandZIndex(float min, float max) {
	distZIndex = uniform_int_distribution(min, max);
	return distZIndex(generator);
}

float WorldRand::getRandRad() {
	return this->getRandRad(0, 2*M_PI);
}

float WorldRand::getRandHeight() {
	return this->getRandRad(0, World::MAX_HEIGHT);
}

unsigned int WorldRand::getRandZIndex() {
	return this->getRandZIndex(0, World::MAX_LAYERS);
}

WorldPos WorldRand::genRandPos() {
	return WorldPos(this->getRandRad(), this->getRandZIndex(), this->getRandHeight());
}
