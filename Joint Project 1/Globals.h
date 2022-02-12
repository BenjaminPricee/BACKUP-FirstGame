// Contains the game globals
#pragma once

//The direction the sprite is moving in
const int static WEST = 1;
const int static EAST = 2;
const int static NORTH = 3; // direction north
const int static SOUTH = 4;

// Screen sizes
const int SCREEN_WIDTH = 1024;   
const int SCREEN_HEIGHT = 640;

// MAX for Arrays
const int MAX_UFOS = 20;
const int MAX_HOSTAGES = 5;

// BAYS for inactive sprites
const int BULLET_BAY = -100;
const int HEART_BAY = -100;
const int HOSTAGE_BAY = -100;