#ifndef src/gamelogic/WorldResource_h_INCLUDED
#define src/gamelogic/WorldResource_h_INCLUDED

#include <string>

using namespace std;

class WorldResource{
	private:
		string name;
		unsigned int amount;
	protected:
		WorldResource();
	public:

		virtual string getName();
		virtual unsigned int getAmount();

		virtual void setAmount();
};

#endif // src/gamelogic/WorldResource_h_INCLUDED

