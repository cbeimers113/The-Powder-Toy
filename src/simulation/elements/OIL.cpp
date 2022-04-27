#include "simulation/ElementCommon.h"

static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_OIL()
{
	Identifier = "DEFAULT_PT_OIL";
	Name = "OIL";
	FullName = "Oil";
	Colour = PIXPACK(0x404010);
	MenuVisible = 1;
	MenuSection = SC_ORGANIC;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 5;

	Weight = 20;

	HeatConduct = 42;
	Description = "Low-carbon oil. Flammable, turns into GAS at low pressure or high temperature. Can be formed with NEUT and NITR.";

	Properties = TYPE_LIQUID | PROP_NEUTPASS;

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
	// Initialize OIL as somewhere in the range of pentane to decane
	sim->parts[i].life = RNG::Ref().between(5, 10);
	sim->parts[i].tmp = (sim->parts[i].life + RNG::Ref().between(-1, 1)) * 2;
}