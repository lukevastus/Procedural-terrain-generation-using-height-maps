# Procedural-terrain-generation-using-height-maps
Randomly generates a 2D terrain height map. 

The heights of tiles are represented using ascii characters, with reference to the descriptions in this site:
http://paulbourke.net/dataformats/asciiart/

The terrain is supposed to be smooth (i.e. the height difference between adjacent tiles is controlled within a small interval). 

Waterbodies are added into the terrain using recursive flood fill algorithm (https://en.wikipedia.org/wiki/Flood_fill), generating ponds, lakes and rarely, rivers. 

RNG interface & implementation provided by Howard Stahl, UCLA.
