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
        sim->create_part(-1, decompX, decompY, sim->parts[i].type);
        sim->parts[i].tmp4--;
        sim->pv[y / CELL][x / CELL] += 5;
    }
}