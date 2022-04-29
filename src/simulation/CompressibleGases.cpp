#include "CompressibleGases.h"

void update_compressible_gases(int i, Simulation *sim)
{
    int x = (int)(sim->parts[i].x + 0.5f);
    int y = (int)(sim->parts[i].y + 0.5f);

    int decompX = -1;
    int decompY = -1;
    int min_compression = 50;

    float pressure = sim->pv[y / CELL][x / CELL];

    for (int xx = -1; xx <= 1; xx++)
    {
        int xOffs = x + xx;
        if (xOffs < 0 || xOffs >= XRES)
            continue;

        for (int yy = -1; yy <= 1; yy++)
        {
            int yOffs = y + yy;
            if (yOffs < 0 || yOffs >= YRES)
                continue;

            int adj = sim->pmap[yOffs][xOffs];

            if (!adj)
            {
                decompX = xOffs;
                decompY = yOffs;
                continue;
            }

            if (i == ID(adj) || sim->parts[ID(adj)].type != sim->parts[i].type)
                continue;

            if (sim->parts[i].tmp4 < 5 && !sim->parts[ID(adj)].tmp4 && pressure > min_compression + sim->parts[i].tmp4 * 25)
            {
                // Hydrocarbons will become more complex when compressed
                if(sim->parts[i].type == PT_GAS)
                {
                    sim->parts[i].life += sim->parts[ID(adj)].life;
                    sim->parts[i].tmp += sim->parts[ID(adj)].tmp;
                }

                int g = sim->parts[ID(adj)].tmp4;
                sim->parts[i].tmp4 += !g ? 1 : g;
                sim->pv[y / CELL][x / CELL] -= 5;
                sim->kill_part(ID(adj));
            }
        }
    }

    // Decompression
    if (sim->parts[i].tmp4 && (decompX + decompY > 0) && pressure <= min_compression + sim->parts[i].tmp4 * 25)
    {
        int g = sim->create_part(-1, decompX, decompY, sim->parts[i].type);

        if (g != -1)
        {
            sim->parts[i].tmp4--;
            sim->pv[y / CELL][x / CELL] += 5;

            if(sim->parts[i].type == PT_GAS)
            {
                int C = sim->parts[i].life;
                int H = sim->parts[i].tmp;
                int gC = C / 2;
                int gH = H / 2;
                C -= gC;
                H -= gH;

                sim->parts[i].life = C;
                sim->parts[i].tmp = H;
                sim->parts[ID(g)].life = gC;
                sim->parts[ID(g)].tmp = gH;
            }
        }
    }
}