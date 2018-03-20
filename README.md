#Orbit-Projection
Project aimed at solving differential equations of orbital motion

Asteroid Orbit Projection project

Finished December 2017

University of Minnesota

Motivated by the discovery of the Oumuamua asteroid in October 2017, I was able to build a program centered around solving ordinary differential equations of motion in order to predict the future trajectory of the asteroid as it traverses and eventually leaves our solar system.

Two .cpp files exist in this repository, both of them represent the final stages of this project. I was able to build programs that, given initial conditions for position and velocity, return data for radial distance from the sun and velocity magnitudes from time 0 up to a time of 7 years ("asteroid1.cpp" for finding radial distance and "asteroid2.cpp" for finding velocity magnitudes). The time steps used in the program were uniform and established in earlier parts of development, and when using those same time steps, there were 627,722 intervals needed to reach 7 years' time.

Corresponding data and graph files (.txt and .jpg, respectively) are also included in this repository. These files show the output of the programs. The .txt files are raw lists of the output of each program, each containing two columns of data. The first column in each is the time elapsed after initial conditions, and the second column shows the radial distance or velocity magnitude, depending on which program was used. The graphs show how radial distances and velocities change over a time span of 7 years. 
