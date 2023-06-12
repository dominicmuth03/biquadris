#include <iostream>
#include "coordinates.h"

#define width 11

Coordinates::Coordinates(int x, int y) : x{x}, y{y} {}

bool Coordinates::operator==(Coordinates &other) { return ((x == other.x) && (y == other.y)); }

int Coordinates::index() { return ((width * y) + x); }

void Coordinates::update(int deltaX, int deltaY)
{
    x += deltaX;
    y += deltaY;
}

int Coordinates::getX() { return x; }

int Coordinates::getY() { return y; }

bool Coordinates::removed() { return (x == -1 && y == -1); }
