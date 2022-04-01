#include <iostream>
#include "objMaker.h"

using namespace std;

int main() {
    float vertices[] = {1,1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1};

    ObjMaker cube ("cube.obj", "cube", 8, vertices, 6, 12);

    cube.create_triangle(1,2,3,1);
    cube.create_triangle(1,3,4,1);

    cube.create_triangle(5,6,7,2);
	cube.create_triangle(5,7,8,2);

	cube.create_triangle(4,3,6,3);
	cube.create_triangle(4,6,5,3);

	cube.create_triangle(8,7,2,4);
	cube.create_triangle(8,2,1,4);

	cube.create_triangle(3,2,7,5);
	cube.create_triangle(3,7,6,5);

	cube.create_triangle(1,4,5,6);
	cube.create_triangle(1,5,8,6);

    cube.create_obj();

    return 0;
}