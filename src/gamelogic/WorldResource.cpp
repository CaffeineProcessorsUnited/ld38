#include "WorldResource.h"

string WorldResource::getName() {
	return this->name;
}

unsigned int WorldResource::getAmount() {
	return this->amount;
}

void WorldResource::setAmount(unsigned int value) {
	this->amount = value;
}
