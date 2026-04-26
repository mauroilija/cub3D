# cub3D

*This project has been created as part of the 42 curriculum by abita, milija-h.*

## Introduction
This project is a team effort inspired by Wolfenstein game, which was the first FPS ever. Our goal is to recreate that experience from scratch, by taking a simple 2D map as
input and producing a navigable 3D environment rendered in real time. The project is divided into two modules. The **parser**, it is responsible for reading and validating the map file: extracting the grid, scene configuration, and any game parameters, then exposing them through a shared interface. The **graphics** uses the data and handles everything the player sees, through raycasting, which is used to project a 3D perspective from a 2D grid, here mentioning wall rendering, field view, and player movement.
The end result is a 3D environment which allows you to move around it and check its boundaries. 

## How to use it
To install the project:
```
git clone git@github.com:arselabita/cub3D.git
```

After the project is cloned, cd into the directory and at the terminal run: 
```
make         # to build/compile the project
make re      # to rebuild/recompile from scratch
make clean   # to remove the .obj files
make fclean  # to remove the .obj files and the executable 
```

The executable of the project is **./cub3D** right next to it you need to pass another argument: 
**path** of the map, in this repo included is a directory called maps there you will find different types, you can choose between to see different textures and map styles:
An example how to run it with a specific map:
```
./cub3D maps/map7.cub
```

To navigate in the GUI use
```
The Arrow keys
The `W/A/S/D` keys
```

To close the window
```
Use `Esc` key
Click the `X` button on the screen
```

## Resources
Useful resources for this project are:
- Minilibx: [hsmits MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- Minilibx: [gontjarow's MiniLibX tutorial](https://gontjarow.github.io/MiniLibX/)
- Raycasting: [Raycasting article](https://www.scottsmitelli.com/articles/we-can-fix-your-raycaster/)
- Raycasting: [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- Raycasting: [3DSage Make Your Own Raycaster](https://www.youtube.com/watch?v=gYRrGTC7GtACub3D)

## Useage of AI
AI tools were used responsibly during development in accordance with the **42 AI policy**.
No AI generated code was integrated, all core logic, parsing, graphics, and math were implemented manually. **Peer reviews** and manual testing were the primary validation methods.
