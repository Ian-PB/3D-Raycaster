#pragma once

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;

const double PI = 3.14159265359;
const double P2 = PI / 2; // P2 = 1.57
const double P3 = 3 * PI / 2; // P3 = 4.71
const double DEGREE_R = 0.0174533;
const int LIGHT_REACH = 100;

/// ------- Colors ------- ///

// Walls
const sf::Color WALL_COLOR = { 0, 0, 0, 255 };
const sf::Color INVIS_COLOR = { 0, 255, 0, 255 };
const sf::Color TRAP_COLOR = { 255, 0, 0, 255 };
const sf::Color DOOR_COLOR = { 0, 0, 255, 255 };

const sf::Color SIDE_COLOR_CHANGE = { 75, 75, 75, 255};

// Light
const sf::Color LIGHT_COLOR = { 255, 255, 100, 5 };