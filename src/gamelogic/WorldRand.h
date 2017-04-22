#ifndef WorldRand_h_INCLUDED
#define WorldRand_h_INCLUDED

#include "WorldObject.h"

using namespace std;

class WorldRand{
	private:
		random_device generator;
		uniform_real_distribution<float> distRad;
		uniform_int_distribution<int> distZIndex;
		uniform_real_distribution<float> distHeight;
    	public:
        	WorldRand();

        	float getRandRad();
        	float getRandRad(float min, float max);
		unsigned int getRandZIndex();
		unsigned int getRandZIndex(unsigned int min, unsigned int max);
		float getRandHeight(); 
		float getRandHeight(float min, float max); 

		WorldPos genRandPos();
};

#endif // WorldRand_h_INCLUDED

