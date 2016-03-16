//
//  Terrain.hpp
//  Terrain_Demo
//
//  Created by Runjia Li on 3/4/16.
//  Copyright © 2016 Runjia Li. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp
#define SIZEMAX 100
#include <iostream>

using namespace std;

class Terrain
{
private:
    int height;
    int width;
    int tiles [SIZEMAX][SIZEMAX];
    bool evtiles [SIZEMAX][SIZEMAX];
    
public:
    Terrain();
    Terrain(int h, int w);
    int heightDiff(int a, int b, int c, int d);
    void genAlt();
    void rgenAlt();
    void flood(int i, int j);
    void genWater();
    void printTerrain();
    void printMtWater();
    double calcWater();
    bool isValidTile(int i, int j);
};


#endif /* Terrain_hpp */
