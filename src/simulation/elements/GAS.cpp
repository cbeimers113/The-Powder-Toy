#include "simulation/ElementCommon.h"

static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_GAS()
{
	Identifier = "DEFAULT_PT_GAS";
	Name = "GAS";
	FullName = "Natural Gas";
	Colour = PIXPACK(0xE0FF20);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 1.0f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.1f;
	Gravity = 0.0f;
	Diffusion = 0.75f;
	HotAir = 0.001f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 1;

	HeatConduct = 42;
	Description = "Natural hydrocarbon gas. Diffuses quickly and is flammable. Liquefies under pressure.";

	Properties = TYPE_GAS | PROP_NEUTPASS;

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
	// Initialize GAS as somewhere in the range of methane to butane
	sim->parts[i].life = RNG::Ref().between(1, 4);
	sim->parts[i].tmp = (sim->parts[i].life + RNG::Ref().between(-1, 1)) * 2;
}
