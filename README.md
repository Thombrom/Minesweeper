# Minesweeper

Minesweeper project

This is a rather small minesweeper project that I have been working on for the first month of the summer of 2021. The motivation for this project stems from the fact that I believe the regular Windows Minesweeper has too many ads. These ads would also not adjust for your current sound volume, such that they would blast sound through your headphones. The second reason is that it does not allow for very big boards (expert is the largest)

This implementation fixes this and allows for as big boards you might want. Right now it is capped at 100 x 100 with max 50% filled mines, however that can be changed by altering the definitions in the settings layer. 

To play this, download and generate the project using premake (generate.bat or generate.sh). Afterwards compile the project and run it from a directory where the resources folder is located (found in src). It has currently been tested on Ubuntu and partly on Windows 10.
