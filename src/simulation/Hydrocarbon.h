#ifndef HYDROCARBON_H
#define HYDROCARBON_H

#include "common/String.h"
#include "common/tpt-rand.h"

bool is_alkane(int C, int H);
bool is_alkene(int C, int H);
bool is_alkyne(int C, int H);

float get_melting_point(int C);
float get_boiling_point(int C);

String get_hydrocarbon_name(int C, int H);

#endif