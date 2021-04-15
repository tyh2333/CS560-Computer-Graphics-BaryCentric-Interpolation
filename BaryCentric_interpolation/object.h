#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> /// for istringstream : for input
using namespace std;
class Object {
public:
    class Vertex{
    public:
       float x, y, z;
    };
    class Face{
    public:
       int a, b, c;
    };
    /// vectors for saving info of v and f in the .obj
    vector<Vertex> vertexes;
    vector<Face> faces;
    void read(const string& pic){
        string line; /// Read in one line every time
        string header; /// The first letter in every line : v and f
        ifstream read(pic);
        while(getline(read, line)){
            istringstream input(line); /// use c++ library sstream
            input >> header; /// read header , v or f , stand for vertexes or faces respectively.
            if(header == "v"){
                Vertex v{}; float x, y, z;
                input >> x >> y >> z;
                v.x = x; v.y = y; v.z = z;
                vertexes.push_back(v);
            }
            else if(header == "f"){
                Face f; int a, b, c;
                input >> a >> b >> c;
                f.a = a; f.b = b; f.c = c;
                faces.push_back(f);
            }
        }
    }
    void draw(){
        for(Face f: faces){
            glBegin(GL_LINE_LOOP);
            glVertex3f(vertexes[f.a-1].x, vertexes[f.a-1].y, vertexes[f.a-1].z);
            glVertex3f(vertexes[f.b-1].x, vertexes[f.b-1].y, vertexes[f.b-1].z);
            glVertex3f(vertexes[f.c-1].x, vertexes[f.c-1].y, vertexes[f.c-1].z);
            glEnd();
        }
    }
};
#endif