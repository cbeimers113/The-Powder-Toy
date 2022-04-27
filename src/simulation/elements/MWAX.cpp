#include "simulation/ElementCommon.h"

static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_MWAX()
{
	Identifier = "DEFAULT_PT_MWAX";
	Name = "MWAX";
	FullName = "Melted Wax";
	Colour = PIXPACK(0xE0E0AA);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.3f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.95f;
	Loss = 0.80f;
	Collision = 0.0f;
	Gravity = 0.15f;
	Diffusion = 0.00f;
	HotAir = 0.000001f* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 2;

	Weight = 25;

	HeatConduct = 44;
	Description = "High-carbon liquid wax. Boils into GAS.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Create = &create;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	// Initialize MWAX as somewhere in the range of undecane to isocane
	sim->parts[i].life = RNG::Ref().between(11, 20);
	sim->parts[i].tmp = (sim->parts[i].life + RNG::Ref().between(-1, 1)) * 2;
}