#include <cstdlib>
#include <GLUT/glut.h>
#include <vector>
#include "basic.h"
using namespace std;
bool Triangle::if_point_in_triangle(Point p){
    BaryCentric pb = convert_to_bary(p);
    bool valid = (pb.l1 >= 0)
              && (pb.l1 <= 1)
              && (pb.l2 >= 0)
              && (pb.l2 <= 1)
              && (pb.l3 >= 0)
              && (pb.l3 <= 1);
    return valid;
}

Point Triangle::convert_to_standard(BaryCentric b){
    float x = b.l1 * p1.x + b.l2 * p2.x + b.l3 * p3.x;
    float y = b.l1 * p1.y + b.l2 * p2.y + b.l3 * p3.y;
    return {static_cast<int>(x), static_cast<int>(y)};
}

BaryCentric Triangle::convert_to_bary(Point p){
    float lam1_top = (p2.y - p3.y) * (p.x - p3.x)  + (p3.x - p2.x) * (p.y - p3.y);
    float lam1_bot = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
    float lam2_top = (p3.y - p1.y) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.y);
    float lam2_bot = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
    float lam1 = lam1_top / lam1_bot;
    float lam2 = lam2_top / lam2_bot;
    float lam3 = 1 - lam1 - lam2;
    return BaryCentric(lam1, lam2, lam3);
}

void Triangle::draw(int x_0, int y_0){
    glBegin(GL_POINTS);
    /// texture stored by paired
    for(auto t: texture){
        Point tmp_point = convert_to_standard(t.first);
        Pixel color = t.second;
        tmp_point.rotate(p3, rot);
        glColor3ub(color.r, color.g, color.b);/// control color
        glVertex2i(tmp_point.x + x_0, tmp_point.y + y_0); /// control position
        glVertex2i(tmp_point.x+1 + x_0, tmp_point.y+1 + y_0);
    }
    glEnd();
}

Flower::Flower(){
    read("./pic/flower.bmp");
    /// After reading the info of the bmp, we can get the height and width.
    /// According the top_left and bottom_right can calculate whole four vertexes of rectangle.

    /// top left vertex
    int x_top_left = 0;
    int y_top_right = 0;
    /// bottom right vertex
    int x_bottom_right = height;
    int y_bottom_right = width;
    /// Get center point
    Point p((x_top_left + x_bottom_right)/2,
            (y_top_right + y_bottom_right)/2);
    /// Get four corner points
    Point top_left     = Point(x_top_left, y_top_right);
    Point top_right    = Point(x_bottom_right, y_top_right);
    Point bottom_left  = Point(x_top_left, y_bottom_right);
    Point bottom_right = Point(x_bottom_right, y_bottom_right);
    /// By using any two vertexes and the center point can generate one triangle.
    /// So 4 in total
    Triangle t = Triangle(top_left, top_right, p);
    Triangle r = Triangle(top_right, bottom_right, p);
    Triangle b = Triangle(bottom_left, bottom_right, p);
    Triangle l = Triangle(bottom_left, top_left, p);

    /// fill list of triangles
    triangles = {t, r, b, l};
    make_texture();
}

void Flower::read(char * filename){
    int HEADER_SIZE = 54;
    int WIDTH_LOCATION = 18;
    int HEIGHT_LOCATION = 22;
    FILE * fd = fopen(filename,"rb");
    /// test
    /*
    static GLint ImageWidth;
    static GLint ImageHeight;
    static GLint PixelLength;
    fseek(fd, 0x0012, SEEK_SET);
    fread(&ImageWidth, sizeof(ImageWidth), 1, fd);
    fread(&ImageHeight, sizeof(ImageHeight), 1, fd);
    cout<<"ImageWidth: "<<ImageWidth<<endl;
    cout<<"ImageHeight: "<<ImageHeight<<endl;
    PixelLength =3 * width * height;
    */
    ///
    unsigned char info[HEADER_SIZE];
    fread(info, sizeof(unsigned char), HEADER_SIZE, fd);
    /// casts that pointer to be a pointer to integer
    width  = *(int *)&info[WIDTH_LOCATION];
    height = *(int *)&info[HEIGHT_LOCATION];
    int PixelLength = 3 * width * height;
    auto * data = (unsigned char *) malloc(sizeof(unsigned char) * PixelLength);
    fread(data, sizeof(unsigned char), PixelLength, fd);/// read data
    fclose(fd);

    /// change order from BGR to RGB.
    for (int i = 0; i < PixelLength; i += 3){
        unsigned char temp = data[i];
        data[i] = data[i+2];
        data[i+2] = temp;
    }
    for(int h = 0; h < height; h++){
        /// convert to 2d vector
        pixels.emplace_back();
        /// make pixels
        for(int w = 0; w < width; w++){
            pixels[h].push_back(Pixel(data[width * h * 3 + w * 3],
                                    data[width * h * 3 + w * 3 + 1],
                                     data[width * h * 3 + w * 3 + 2]));
        }
    }
    free(data);
}

void Flower::make_texture(){
    /// generate texture for each triangle
    for(unsigned long row = 0; row < pixels.size(); row++){
        for(unsigned long col = 0; col < pixels[0].size(); col++){
            for(Triangle& t: triangles){
                if(t.if_point_in_triangle(Point(row, col))){
                    t.texture.emplace_back(t.convert_to_bary(Point(row, col)), pixels[row][col]);
                }
            }
        }
    }
}

void Flower::draw(){
    /// triangles = {t, r, b, l};
    for(auto t: triangles){
        t.draw(offset_x, offset_y);
    }
}
void Flower::current_click_point(Point p){
    /// update the 4 triangles, triangles = {t, r, b, l};
    for(auto& t: triangles){
        t.p3 = Point(p.x - offset_x, p.y - offset_y);
    }
}