# Game Engine

## Introduction

This was part of a Computer Graphics module. Then aim of this project was to develop a game engine, so that the code that I wrote is entirely re-usable. The scene that was demonstrated was built from a description in text files, and as such can be modified without recompiling the program. Indeed, the entire scene can be changed, with different objects and hierarchies, and different key presses to interact with the program.

## Requirements and installation

This was tested on macOS and Clang and will likely not work on other operating systems without minor modification. The following libraries are used

 * GLEW
 * GLFW
 * GLM
 * DevIL
 * Assimp

Build using _Make_.

## Usage

An example startup is as follows:

```./main ancillary/setup/data.txt ancillary/setup/actions.txt```

For a more complete explanation and reference, see _report.pdf_.