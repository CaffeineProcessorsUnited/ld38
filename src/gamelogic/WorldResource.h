#ifndef WorldResource_h_INCLUDED
#define WorldResource_h_INCLUDED

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

		virtual void setAmount(unsigned int value);
};

#endif // WorldResource_h_INCLUDED

