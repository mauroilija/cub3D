# cub3D

*This project has been created as part of the 42 curriculum by abita, milija-h.*

## Introduction
This project is a team effort inspired by Wolfenstein game, which was the first FPS ever. Our goal is to recreate that experience from scratch, by taking a simple 2D map as
input and producing a navigable 3D environment rendered in real time. The project is divided into two modules. The **parser**, it is responsible for reading and validating the map file: extracting the grid, scene configuration, and any game parameters, then exposing them through a shared interface. The **graphics** uses the data and handles everything the player sees, through raycasting, which is used to project a 3D perspective from a 2D grid, here mentioning wall rendering, field view, and player movement.
The end result is a 3D environment which allows you to move around it and check its boundaries. 

## How to use it?
To install the project:
```
git clone git@github.com:arselabita/cub3D.git
```
After the project is cloned, cd into the directory and at the terminal run: 
```
make
```
the binary of the project is **./cub3D** right next to it you need to pass another argument: **path** of the map, in this repo included is a directory called maps there you will find different types, you can choose between to see different textures and map styles:
An example how to run it with a specific map:
```
./cub3D maps/map7.c
```
To navigate in the GUI use
```
The arrow keys and
the WASD keys
```

## Resources
Useful resources for this project are:
- Minilibx: [hsmits MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- Minilibx: [gontjarow's MiniLibX tutorial](https://gontjarow.github.io/MiniLibX/)
- Raycasting: [Raycasting article](https://www.scottsmitelli.com/articles/we-can-fix-your-raycaster/)
- Raycasting: [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- Raycasting: [3DSage Make Your Own Raycaster](https://www.youtube.com/watch?v=gYRrGTC7GtACub3D)
- Flood Fill: [Flood Fill Algorithm](https://darrenyao.com/usacobook/cpp.pdf#page=51)
- Flood Fill: [Flood Fill - Labeling/Coloring the Connected Components](https://usaco.guide/CP2.pdf#page=90)
