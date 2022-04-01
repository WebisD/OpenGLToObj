#ifndef OBJMAKER_H
#define OBJMAKER_H

#include "glm.h"

class ObjMaker{
   private:
      char* path_name;
      char* name;
      int num_vertices;
      float* vertices_array;
      int num_normals;
      int num_triangles;
      int triangles_list_index;
      GLMtriangle* triangles_list;
        
   public:
      ObjMaker(char* path_name, char* name, int num_vertices, float vertices_array[], int num_normals, int num_triangles);
      
      void create_triangle(int tri_index_a, int tri_index_b, int tri_index_c, int normal);

      void create_obj();
};

#endif