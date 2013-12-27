#ifndef BEE_H
#define BEE_H
#include <string>

#include "Entity.h"

class Bee : public Entity{
	public:
		Bee(int posx, int posy, std::string name);
		void addPoint();
	private:
		int points;
};
#endif