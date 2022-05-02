#include "simulation/ElementCommon.h"
#include "simulation/Hydrocarbon.h"

int hydrocarbon_update(UPDATE_FUNC_ARGS);
void hydrocarbon_create(ELEMENT_CREATE_FUNC_ARGS);

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

	Update = &hydrocarbon_update;
	Create = &hydrocarbon_create;
}

int hydrocarbon_update(UPDATE_FUNC_ARGS)
{
	// Clamp the number of carbons and hydrogens
	// If dealing with methane, there is only one possible configuration
	if (parts[i].life <= 1)
	{
		parts[i].life = 1;
		parts[i].tmp = 4;
	}
	// If the carbon chain is too long, shorten it to a random long molecule
	else if (parts[i].life > 60)
	{
		parts[i].life = RNG::Ref().between(1, 6) * 10;
		parts[i].tmp = (parts[i].life + RNG::Ref().between(-1, 1)) * 2;
	}
	// Otherwise check number of hydrogens
	else if (!(is_alkane(parts[i].life, parts[i].tmp) || is_alkene(parts[i].life, parts[i].tmp) || is_alkyne(parts[i].life, parts[i].tmp)))
	{
		// Reassign the number of hydrogens randomly
		parts[i].tmp = (parts[i].life + RNG::Ref().between(-1, 1)) * 2;
	}

	// Perform state changes
	float melting_point = get_melting_point(parts[i].life);
	float boiling_point = get_boiling_point(parts[i].life);
	float temp = parts[i].temp - sim->pv[y / CELL][x / CELL]; // As pressure increases, higher temps are required to melt/boil

	// Should be a solid
	if (temp < melting_point)
	{
		int solid_type = PT_WAX;

		if (parts[i].type != solid_type)
			sim->part_change_type(i, x, y, solid_type);
	}
	// Should be a liquid
	else if (temp < boiling_point)
	{
		int liquid_type = parts[i].life < 11 ? PT_OIL : PT_MWAX;

		if (parts[i].type != liquid_type)
			sim->part_change_type(i, x, y, liquid_type);
	}
	// Should be a gas
	else
	{
		int gas_type = PT_GAS;

		if (parts[i].type != gas_type)
			sim->part_change_type(i, x, y, gas_type);
	}

	for (int ry = -2; ry <= 2; ry++)
		for (int rx = -2; rx <= 2; rx++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = sim->pmap[y + ry][x + rx];

				if (!r)
					continue;

				// If this molecule collides with a small hydrocarbon and it's hot enough, join them together
				if (TYP(r) == PT_GAS && parts[ID(r)].life < 5 && RNG::Ref().chance(1, 10) &&
					(parts[ID(r)].temp + parts[i].temp) / 2 > 273.15f + parts[i].life * 100 - sim->pv[y / CELL][x / CELL])
				{
					parts[i].life += parts[ID(r)].life;
					parts[i].tmp += parts[ID(r)].tmp;
					sim->kill_part(ID(r));
				}
			}

	return 0;
}

void hydrocarbon_create(ELEMENT_CREATE_FUNC_ARGS)
{
	// Initialize GAS as somewhere in the range of methane to butane
	if (sim->parts[i].type == PT_GAS)
		sim->parts[i].life = RNG::Ref().between(1, 4);

	// Initialize OIL as somewhere in the range of pentane to decane
	else if (sim->parts[i].type == PT_OIL)
		sim->parts[i].life = RNG::Ref().between(5, 10);

	// Initialize MWAX as somewhere in the range of undecane to isocane
	else if (sim->parts[i].type == PT_MWAX)
		sim->parts[i].life = RNG::Ref().between(11, 20);

	// Initialize WAX as somewhere in the range above isocane
	else
		sim->parts[i].life = RNG::Ref().between(21, 60);

	sim->parts[i].tmp = (sim->parts[i].life + RNG::Ref().between(-1, 1)) * 2;
}
