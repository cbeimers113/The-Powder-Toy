#ifndef IONS_H
#define IONS_H

#include "common/String.h"

// For elements which can form ions
struct IonData
{
    String symbol;
    int charge;
    float electroneg;

    IonData() : symbol("Ion"), charge(0), electroneg(0) {}
    IonData(String _symbol, int _charge, float _electroneg) : symbol(_symbol), charge(_charge), electroneg(_electroneg) {}
};

#endif