# fractalC

C project which generates images based on the behaviour of complex valued functions under repeated iteration. 

## Description

The project uses an escape time algorithm to visualize the number of iterations it takes for a certain point in the complex plane to reach a certain threshhold or diverge of to infinity. (https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set)
It is just a fun project of mine and is not well documented and currently lacks error handling.
Users may add their own functions to study their behaviour using the image generation offered by the project.

## Getting Started

### Dependencies

* This project uses stb libraries (included in lib) to generate PNG images. Alternatively, ppm images can be generated without the use of the stb libraries.
* Building should work by running the makefile, but was not properly tested.

### Installing

* Download the repository and run 'make' to build.
* All paths are relative by default and the structure of the repo is assumed.

### Executing program

* There is no gui or commandline interface by default. The main.c file currently defines the behaviour of the programm.

## Credits

* Checkout all other stb libraries: https://github.com/nothings/stb
