# Minesweeper

Minesweeper project

This is a rather small minesweeper project that I have been working on for the first month of the summer of 2021. The motivation for this was for one that I thought the regular Windows Minesweeper had too many adds sometimes. Also they would not adjust the sound of those ads such that it could sometimes really chok you when playing. But more importantly, they did not allow you to set the size of their board very high.

This implementation fixes this and allows for however big boards you might want. Right now it is capped at 100 x 100 with max 50% filled mines, however that can be changed by altering the definitions in the settings layer. 

To play this, download and generate the project using premake (generate.bat or generate.sh). Afterwards compile the project and run it from a directory where the resources folder is located (found in src). It has currently been tested on Ubuntu and partly on Windows 10.
