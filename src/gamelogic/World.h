#ifndef src/gamelogic/World_h_INCLUDED
#define src/gamelogic/World_h_INCLUDED

#include <WorldResource.h>
#include <WorldObject.h>
#include <vector>

using namespace std;

class World{
	private:
		vector<WorldResource*> resources;
		vector<WorldObject*> objects;
	public:
		World();
		const static unsigned int MAX_LAYERS;
		vector<WorldResource*>& getResources();
		vector<WorldResource*>& getObjects();

		void update(float time_delta);
};

#endif // src/gamelogic/World_h_INCLUDED

