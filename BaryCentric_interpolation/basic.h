#ifndef BASICS_H
#define BASICS_H

#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
class Point{
public:
    int x, y;
    Point() = default;
    Point(int x_input, int y_input){
        x = x_input; y = y_input;
    }
    void rotate(Point origin, float angle){
        double s = sin(angle * M_PI/180);
        double c = cos(angle * M_PI/180);
        double delta_x = (x -origin.x)*c - (y - origin.y)*s;
        double delta_y = (x -origin.x)*s + (y - origin.y)*c;
        x = int(delta_x + origin.x);
        y = int(delta_y + origin.y);
    }
};

class BaryCentric{
public:
    float l1, l2, l3; /// three members : lambda 1,lambda 2, lambda3
    BaryCentric() = default;
    BaryCentric(float lambda1, float lambda2, float lambda3){
        l1 = lambda1; l2 = lambda2; l3 = lambda3;
    }
};

class Pixel{
public:
    unsigned char r, g, b;
    Pixel() = default;
    Pixel(unsigned char red, unsigned char green, unsigned char blue){
        r = red; g = green; b = blue;
    }
};

class Triangle{
public:
    Point p1{}, p2{}, p3{};
    float rot = 0;
    vector<pair<BaryCentric, Pixel>> texture;
    Triangle() = default;
    Triangle(Point point1, Point point2, Point point3){
        p1 = point1; p2 = point2; p3 = point3;
    }
    /// Check if p3 in the right triangle, argument p3
    bool if_point_in_triangle(Point);
    /// bary <-> standard, change of coordinate
    Point convert_to_standard(BaryCentric);
    BaryCentric convert_to_bary(Point);
    /// draw triangles, arguments : x and y
    void draw(int, int);
};

class Flower{
public:
    int offset_x = 200;
    int offset_y = 200;
    int rot{};
    int width{}, height{};
    Point current_click{};
    vector<vector<Pixel>> pixels;
    vector<Triangle> triangles;

    Flower();
    void read(char*);
    void make_texture();
    void draw(); /// using triangle.draw to draw four triangles.
    /// In mouse and move function, passing current_click_point to point 3 to build new triangels.
    void current_click_point(Point);
};
#endif
