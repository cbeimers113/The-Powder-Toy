#include "simulation/ElementCommon.h"

int hydrocarbon_update(UPDATE_FUNC_ARGS);
void hydrocarbon_create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_WAX()
{
	Identifier = "DEFAULT_PT_WAX";
	Name = "WAX";
	FullName = "Wax";
	Colour = PIXPACK(0xF0F0BB);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 10;

	Weight = 100;

	HeatConduct = 44;
	Description = "Wax. Melts at moderately high temperatures.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &hydrocarbon_update;
	Create = &hydrocarbon_create;
}