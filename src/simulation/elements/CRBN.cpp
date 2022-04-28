#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_CRBN()
{
    Identifier = "DEFAULT_PT_CRBN";
    Name = "CRBN";
    FullName = "Carbon";
    Colour = PIXPACK(0x888888);
    MenuVisible = 1;
    MenuSection = SC_ORGANIC;
    Enabled = 1;

    Advection = 0.7f;
    AirDrag = 0.02f * CFDS;
    AirLoss = 0.96f;
    Loss = 0.80f;
    Collision = 0.0f;
    Gravity = 0.1f;
    Diffusion = 0.00f;
    HotAir = 0.000f * CFDS;
    Falldown = 1;

    Flammable = 0;
    Explosive = 0;
    Meltable = 0;
    Hardness = 30;
    PhotonReflectWavelengths = 0x888888;

    Weight = 85;

    HeatConduct = 70;
    Description = "Carbon dust. Formed from burning WOOD and COAL. Can form organic molecules and be compressed into BCOL.";

    Properties = TYPE_PART;

    LowPressure = IPL;
    LowPressureTransition = NT;
    HighPressure = IPH;
    HighPressureTransition = NT;
    LowTemperature = ITL;
    LowTemperatureTransition = NT;
    HighTemperature = ITH;
    HighTemperatureTransition = NT;

    Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
    int r, rx, ry;

    // Look for 4 hydrogens (2 H2) to create methane
    int H1 = -1;
    int H2 = -1;

    for (rx = -2; rx < 3; rx++)
        for (ry = -2; ry < 3; ry++)
            if (BOUNDS_CHECK && (rx || ry))
            {
                r = pmap[y + ry][x + rx];

                if (!r)
                    continue;

                // Form a hydrocarbon
                if (TYP(r) == PT_H2)
                {
                    if (H1 == -1)
                        H1 = ID(r);
                    else if (H2 == -1)
                        H2 = ID(r);

                    // Create methane if we have all 4 hydrogens
                    if (H1 != -1 && H2 != -1)
                    {
                        parts[i].life = 1;
                        parts[i].tmp = 4;
                        sim->part_change_type(i, x, y, PT_GAS);
                        sim->kill_part(H1);
                        sim->kill_part(H2);
                        return 0;
                    }
                }
                else if((TYP(r) == PT_CRBN || TYP(r) == PT_COAL || TYP(r) == PT_BCOL) && sim->pv[y/CELL][x/CELL] >= 25)
                {
                    parts[ID(r)].life = 100;
                    sim->part_change_type(ID(r), x + rx, y + ry, PT_BCOL);
                    sim->kill_part(i);
                }
            }

    return 0;
}