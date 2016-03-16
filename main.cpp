//
//  main.cpp
//  Terrain_Demo
//
//  Created by Runjia Li on 3/4/16.
//  Copyright © 2016 Runjia Li. All rights reserved.
//

#include <iostream>
#include "Terrain.hpp"

using namespace std;

int main()
{
    Terrain k (50, 100);
    k.rgenAlt();
    k.printTerrain();
    while (k.calcWater() < 5.0)
    {
        k.genWater();
    }
    k.printMtWater();
}
