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
//Constructs an empty terrain map
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
//Constructs an empty terrain map with user given dimensions
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
//Calculates height difference between two tiles
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
//Around tile[i][j], how many tiles are more than 1 unit higher/lower than tile[i][j]?
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
//Generates heights from the top right corner (this results in vertical patterns)
{
    RandomNumber randAlt(1, 9);
    for (int j = 1; j < (width - 1); j++)
    {
        for (int i = 1; i < (height - 1); i ++)
        {
            //Continuously "smoothens" the tile until its height is not overly different from its neighbors 
            do
            {
                tiles[i][j] = randAlt.random();
            } while (!isValidTile(i, j));
        }
        
    }
}

void Terrain::rgenAlt()
//Generates the heights, starting from a random tile
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
        
        //Check if the tile hasn't been assigned a height
        if (tiles[i][j] == 0)
        {
            tiles[i][j] = randAlt.random();
            //Number of attempts to smoothen the tile
            int reassigned = 0;
            //Smoothening: regenerates height of the tile until it does not have much difference with its neighbors 
            while (!isValidTile(i, j) && reassigned <= 100)
            {
                    
                tiles[i][j] = randAlt.random();
                reassigned++;
            }
            //If attempts fail continuously, record the tile as an exception
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
//Floods the adjacent tiles of a "water" tile, changing them to "water" (value 10)
{
    //Stop generating water upon reaching another water body or the map boundaries 
    if (tiles [i][j] == 10 || i <= 2 || i >= (height - 2) || j <= 2 || j >= (width - 2))
    {
        return;
    }
    
    //Water flows down, so in order for a tile to be flooded, 
    //it must have lower height than an adjacent "water" tile
    int prevHeight = tiles [i][j];
    tiles [i][j] = 10;
    //Floods in 4 directions from the current tile
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
//Generates water bodies, starting from a random tile
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
//Plots all the water bodies
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
//Plots the terrain as ASCII grey scale characters
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
//Calculates percentage of water 
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

