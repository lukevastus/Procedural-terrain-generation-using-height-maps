//
//  Terrain.cpp
//  Terrain_Demo
//
//  Created by Runjia Li on 3/4/16.
//  Copyright © 2016 Runjia Li. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "Terrain.hpp"
#include "RandomNumber.h"

using namespace std;

Terrain::Terrain()
{
    height = 100;
    width = 100;
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            tiles[i][j] = 0;
            evtiles[i][j] = 0;
        }
            
    }
}

Terrain::Terrain(int h, int w)
{
    height = h;
    width = w;
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            tiles[i][j] = 0;
            evtiles[i][j] = 0;
        }
        
    }
}

int Terrain::heightDiff(int a, int b, int c, int d)
{
    if (tiles[c][d] == 0)
    {
        return 0;
    }
    else
    {
        return (abs(tiles[a][b] - tiles[c][d]));
    }
}

bool Terrain::isValidTile(int i, int j)
{
    int v = 0;
    if (heightDiff(i, j, i - 1, j) > 1)
    {
        v++;
    }
    if (heightDiff(i, j, i, j - 1) > 1)
    {
        v++;
    }
    if (heightDiff(i, j, i + 1, j) > 1)
    {
        v++;
    }
    if (heightDiff(i, j, i, j + 1) > 1)
    {
        v++;
    }
    if (heightDiff(i, j, i - 1, j - 1) > 2)
    {
        v++;
    }
    if (heightDiff(i, j, i + 1, j + 1) > 2)
    {
        v++;
    }
    if (heightDiff(i, j, i - 1, j + 1) > 2)
    {
        v++;
    }
    if (heightDiff(i, j, i + 1, j - 1) > 2)
    {
        v++;
    }

    if (v > 2)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

void Terrain::genAlt()
{
    RandomNumber randAlt(1, 9);
    for (int j = 1; j < (width - 1); j++)
    {
        for (int i = 1; i < (height - 1); i ++)
        {
            do
            {
                tiles[i][j] = randAlt.random();
            } while (!isValidTile(i, j));
        }
        
    }
}

void Terrain::rgenAlt()
{
    RandomNumber randAlt(1, 9);
    RandomNumber rh(1, (height - 2));
    RandomNumber rw(1, (width - 2));
    int numEvaluated = 0;
    int i = 0;
    int j = 0;
    int numExceptions = 0;
    
    cout << "Generating terrain....." << endl;
    do
    {
        i = rh.random();
        j = rw.random();
        if (tiles[i][j] == 0)
        {
            tiles[i][j] = randAlt.random();
            int reassigned = 0;
            while (!isValidTile(i, j) && reassigned <= 100)
            {
                    
                tiles[i][j] = randAlt.random();
                reassigned++;
            }
                
            if (reassigned > 100)
            {
                numExceptions++;
            }
                
            numEvaluated++;
        }
        
    } while (numEvaluated < (width - 2)*(height - 2));
    
    cout << "Total tiles evaluated:"<< numEvaluated << endl;
    cout << "Number of exceptions:" << numExceptions << endl;
}

void Terrain::flood(int i, int j)
{
    if (tiles [i][j] == 10 || i <= 2 || i >= (height - 2) || j <= 2 || j >= (width - 2))
    {
        return;
    }
    int prevHeight = tiles [i][j];
    tiles [i][j] = 10;
    if (tiles[i + 1][j] <= prevHeight)
    {
        flood(i + 1, j);
    }
    if (tiles[i][j + 1] <= prevHeight)
    {
        flood(i, j + 1);
    }
    if (tiles[i - 1][j] <= prevHeight)
    {
        flood(i - 1, j);
    }
    if (tiles[i][j - 1] <= prevHeight)
    {
        flood(i, j - 1);
    }
}

void Terrain::genWater()
{
    RandomNumber rh(2, (height - 2));
    RandomNumber rw(2, (width - 2));
    int i = 0;
    int j = 0;
    
    do
    {
        i = rh.random();
        j = rw.random();
    } while (tiles [i][j] >= 6);
    flood(i , j);
}

void Terrain::printMtWater()
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tiles[i][j] == 10)
            {
                cout << "~";
            }
            if (tiles [i][j] == 0)
            {
                cout << "";
            }
            if (tiles [i][j] > 0 && tiles [i][j] < 10)
            {
                cout << " ";
            }
            if (j == (width - 1))
            {
                cout << endl;
            }
        }
        
    }
}

void Terrain::printTerrain()
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (tiles[i][j])
            {
                case 1:
                    cout << ".";
                    break;
                case 2:
                    cout << ":";
                    break;
                case 3:
                    cout << "+";
                    break;
                case 4:
                    cout << "*";
                    break;
                case 5:
                    cout << "x";
                    break;
                case 6:
                    cout << "m";
                    break;
                case 7:
                    cout << "#";
                    break;
                case 8:
                    cout << "&";
                    break;
                case 9:
                    cout << "@";
                    break;
                case 0:
                    break;
            }
            if (j == (width - 1))
            {
                cout << endl;
            }
        }
        
    }
}

double Terrain::calcWater()
{
    double waternum = 0;
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            if (tiles[i][j] == 10)
            {
                waternum++;
            }
        }
    }
    double perWater = waternum / ((height - 2) * (width - 2)) * 100.00;
    return perWater;
}

