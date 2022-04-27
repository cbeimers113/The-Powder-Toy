#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Config.h"

#include <vector>

#include "StructProperty.h"

struct Particle
{
	int type;
	int ctype;
	int life;  // Used to store number of carbons for hydrocarbons
	float x, y, vx, vy;
	float temp;
	int flags;
	int tmp;	// Used to store number of hydrogens for hydrocarbons
	int tmp2;
	int tmp3;	// Used as decomposition timer
	int tmp4;	// Used for gas compression
	unsigned int dcolour;

	// non-persistent Cyens Toy Properties
	int time_dilation_timer;

	/** Returns a list of properties, their type and offset within the structure that can be changed
	 by higher-level processes referring to them by name such as Lua or the property tool **/
	static std::vector<StructProperty> const &GetProperties();
};

#endif
