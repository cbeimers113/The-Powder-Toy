#include "Hydrocarbon.h"

bool is_alkane(int C, int H)
{
    return C > 0 && H == 2 * C + 2;
}

bool is_alkene(int C, int H)
{
    return C > 0 && H == 2 * C;
}

bool is_alkyne(int C, int H)
{
    return C > 0 && H == 2 * C - 2;
}

// Gets the point at which transition between solid and liquid state occurs
float get_melting_point(int C)
{
    float melting_point = 273.15f;

    // Real life melting points for 1-10 C alkanes
    switch (C)
    {
    case 1:
        melting_point += -183;
        break;
    case 2:
        melting_point += -182.8f;
        break;
    case 3:
        melting_point += -187;
        break;
    case 4:
        melting_point += -138;
        break;
    case 5:
        melting_point += -130;
        break;
    case 6:
        melting_point += -95;
        break;
    case 7:
        melting_point += -90.5;
        break;
    case 8:
        melting_point += -57;
        break;
    case 9:
        melting_point += -54;
        break;
    case 10:
        melting_point += -30;
        break;
    default:
        // Otherwise estimate
        melting_point += 2 * (C - 10);
    }

    return melting_point;
}

// Gets the point at which transition between liquid and gas state occurs
float get_boiling_point(int C)
{
    float boiling_point = 273.15f;

    // Real life boiling points for 1-10 C alkanes
    switch (C)
    {
    case 1:
        boiling_point += -162;
        break;
    case 2:
        boiling_point += -88.6f;
        break;
    case 3:
        boiling_point += -42;
        break;
    case 4:
        boiling_point += -0.5f;
        break;
    case 5:
        boiling_point += 36;
        break;
    case 6:
        boiling_point += 69;
        break;
    case 7:
        boiling_point += 98;
        break;
    case 8:
        boiling_point += 126;
        break;
    case 9:
        boiling_point += 151;
        break;
    case 10:
        boiling_point += 174;
        break;
    default:
        // Otherwise estimate
        boiling_point += 180 + 10 * (C - 10);
    }

    return boiling_point;
}

String get_hydrocarbon_name(int C, int H)
{
    bool alkane = is_alkane(C, H);
    bool alkene = is_alkene(C, H);
    bool alkyne = is_alkyne(C, H);

    if (!(alkane || alkene || alkyne))
        return "";

    String name = "";

    switch (C)
    {
    case 1:
        name += "meth";
        break;
    case 2:
        name += "eth";
        break;
    case 3:
        name += "prop";
        break;
    case 4:
        name += "but";
        break;
    case 5:
        name += "pent";
        break;
    case 6:
        name += "hex";
        break;
    case 7:
        name += "hept";
        break;
    case 8:
        name += "oct";
        break;
    case 9:
        name += "non";
        break;
    case 10:
        name += "dec";
        break;
    case 11:
        name += "undec";
        break;
    case 12:
        name += "dodec";
        break;
    case 13:
        name += "tridec";
        break;
    case 14:
        name += "tetradec";
        break;
    case 15:
        name += "pentadec";
        break;
    case 16:
        name += "hexadec";
        break;
    case 17:
        name += "heptadec";
        break;
    case 18:
        name += "octadec";
        break;
    case 19:
        name += "nonadec";
        break;
    case 20:
        name += "icos";
        break;
    case 30:
        name += "triacont";
        break;
    case 40:
        name += "tetracont";
        break;
    case 50:
        name += "pentacont";
        break;
    case 60:
        name += "hexacont";
        break;
    default:
        name += "kerosene";
        break;
    }

    if (name != "kerosene")
        name += alkane ? "ane" : alkene ? "ene"
                                        : "yne";

    return name;
}

void update_organic_molecule(int i, Simulation *sim)
{
    Particle *molecule = &(sim->parts[i]);
    int x = (int)(molecule->x + 0.5f);
    int y = (int)(molecule->y + 0.5f);

    // Clamp the number of carbons and hydrogens
    int C = molecule->life;
    int H = molecule->tmp;

    // If dealing with methane, there is only one possible configuration
    if (C <= 1)
    {
        molecule->life = 1;
        molecule->tmp = 4;
    }
    // If the carbon chain is too long, shorten it to a random long molecule
    else if (C > 60)
    {
        molecule->life = RNG::Ref().between(1, 6) * 10;
        molecule->tmp = (molecule->life + RNG::Ref().between(-1, 1)) * 2;
    }
    // Otherwise check number of hydrogens
    else if (!(is_alkane(C, H) || is_alkene(C, H) || is_alkyne(C, H)))
    {
        // Reassign the number of hydrogens randomly
        molecule->tmp = (molecule->life + RNG::Ref().between(-1, 1)) * 2;
    }

    // Reassess structure
    C = molecule->life;
    H = molecule->tmp;

    // Perform state changes
    float melting_point = get_melting_point(C);
    float boiling_point = get_boiling_point(C);
    float temp = molecule->temp - sim->pv[y / CELL][x / CELL]; // As pressure increases, higher temps are required to melt/boil

    // Should be a solid
    if (temp < melting_point)
    {
        int solid_type = PT_WAX;

        if (molecule->type != solid_type)
            sim->part_change_type(i, x, y, solid_type);
    }
    // Should be a liquid
    else if (temp < boiling_point)
    {
        int liquid_type = C < 11 ? PT_OIL : PT_MWAX;

        if (molecule->type != liquid_type)
            sim->part_change_type(i, x, y, liquid_type);
    }
    // Should be a gas
    else
    {
        int gas_type = PT_GAS;

        if (molecule->type != gas_type)
            sim->part_change_type(i, x, y, gas_type);
    }

    // Large hydrocarbons will decompose over time with longer molecules going fastest
    if (C > 4 && RNG::Ref().chance(1, restrict_flt(10000 - (C * 100) - ++molecule->tmp3, 1, 10000)))
    {
        int rx = RNG::Ref().between(-1, 1);
        int ry = -1;
        int np = sim->create_part(-1, x + rx, y + ry, molecule->type);

        if (np > -1)
        {
            Particle *newPart = &(sim->parts[ID(np)]);
            int nC = C / 2;
            int nH = 2 * (RNG::Ref().between(-1, 1) + nC);

            newPart->life = nC;
            newPart->tmp = nH;
            molecule->life -= nC;
            molecule->tmp -= nH;
        }
    }
    // If not decomposing, check if we can form a more complex molecule with surrounding particles
    else
    {
        int r, rx, ry;

        for (ry = -2; ry <= 2; ry++)
            for (rx = -2; rx <= 2; rx++)
                if (BOUNDS_CHECK && (rx || ry))
                {
                    r = sim->pmap[y + ry][x + rx];

                    if (!r)
                        continue;

                    // If this molecule collides with a short-chain hydrocarbon and it's hot enough, join them together
                    if (TYP(r) == PT_GAS && (sim->parts[ID(r)].temp + molecule->temp) / 2 > 273.15f + molecule->life * 100 - sim->pv[y / CELL][x / CELL])
                    {
                        molecule->life += sim->parts[ID(r)].life;
                        molecule->tmp += sim->parts[ID(r)].tmp - 2;
                        sim->part_change_type(ID(r), x + rx, y + ry, PT_H2);
                    }
                }
    }
}