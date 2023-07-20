# Mariomega-Man

## Download
To download the game repo you can go to Code and click Download ZIP. You'll be provided by Mariomega-Man-master.zip, extract the zip and you'll find few folders:

- **assets**    : Contain all the textures, fonts, and all game assets that required in game. Make sure to always include this file to run your game.
- **build**     : In this folder contain the compiled executable file of the game and the necessary items for game to run.
- **include**   : All the include dependencies remain in this folder. If you want to run the code from IDE such as Visual Studio Code or Visual Studio through compiler, you must include this file in your project.
- **lib**       : All the lib dependencies required for this project.
- **src**       : The main source code that later can be compiled or modified, you can always change this code to make your own project

## Run Game
if you want to try the game as soon as possible, you can go to build folder and run the .exe file without any configuration.

## VS Project
another way you can run the code is by using Visual Studio Project File. Make sure you've already install Visual Studio, then go to src folder and search for Mariomega-Man.vcxproj. Open the file and go to Solution Explorer, there you can find the source code in Mariomega-Man project. Before building the code you must specified few dependencies, here's the step:

- Right click in the Mariomega-Man project.
- Go to Properties.
- Click on **C/C++**, in **Addtional Include Directories** click **Edit** and specify the include folder path that you have in this Mariomega-Man repository.
- Click on **Linker**, in **Addtional Library Directories** click **Edit** and specify lib folder path that you have in this Mariomega-Man repository.
- Still on **Linker** click **Input**, in **Additional Dependencies** click **Edit** and specify the following: _**sfml-graphics-d.lib**_, _**sfml-window-d.lib**_, _**sfml-system-d.lib**_, and _**sfml-audio-d.lib**_.
- Finally you can click Apply to save your changes, then click OK if the window still not close.

You are set and ready to go! Click F5 to debug your code and see the magic!

## Game Configuration
In source file there're few configuration file that can be change to setting the game, config.txt and level(num).txt

### Config.txt
In config you'll find columns and rows that provided some informarion. The first column is the game settings you can change followed by their own properties.

### Level(num).txt
In level file config you will the entity creation properties:

- **entity**  : type of entity, Tile for entity that have bounding box, Dec if there's none (i don't implement the Dec yet haha).
- **name**    : the entity name correspond to their animation.
- **FromX**   : the intial x grid coordinate.
- **FromY**   : the inital y grid coordinate.
- **toX**     : the final x grid coordinate.
- **toY**     : the final y grid coordinate.

There's also Building type entity that have different property from normal entity:
- **Pipe**, height for the pipe, gridX and gridY for the inital grid coordinate
- **Pole**, height for the Pole/Flag, gridX and gridY for the inital grid coordinate

You can anytime change this level configuration and create your own unique levels, in fact only the first level is implemented.
