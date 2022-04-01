#include "glm.h"
#include <iostream>

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
        GLMmodel* model;
        
    public:
        ObjMaker(char* path_name, char* name, int num_vertices, float vertices_array[], int num_normals, int num_triangles);        
        
        void create_triangle(int tri_index_a, int tri_index_b, int tri_index_c, int normal);

        void create_obj();  
};

ObjMaker::ObjMaker(char* path_name, char* name, int num_vertices, float vertices_array[], int num_normals, int num_triangles){
    this->path_name = path_name;
    this->name = name;
    this->num_vertices = num_vertices;
    this->vertices_array = vertices_array;
    this->num_normals = num_normals;
    this->num_triangles = num_triangles;
    this->triangles_list = (GLMtriangle*)malloc(sizeof(GLMtriangle)*this->num_triangles);
    triangles_list_index = 0;
}

void ObjMaker::create_obj(){
    if (this->triangles_list_index == 0)
    {
        fprintf(stderr, "You have to create the triangles first\n");
        return;
    }
    this->model = (GLMmodel*)malloc(sizeof(GLMmodel));

    this->model->pathname = this->path_name;
    this->model->mtllibname = NULL;

    this->model->numvertices = this->num_vertices;

    int size = (this->num_vertices*3)+3;
    GLfloat vert[size];
    for (int i = 3, j=0; i < size; i++, j++)
	{
		vert[i] = this->vertices_array[j];
	}
    this->model->vertices = vert;

    this->model->numnormals = this->num_normals;
    this->model->normals = NULL;

    this->model->numtexcoords = 0;

	this->model->numfacetnorms = 0;

	this->model->numtriangles = this->num_triangles;
	this->model->triangles = this->triangles_list;

	this->model->nummaterials = 0;

	this->model->numgroups = 1;

    GLMgroup grupos[1];
	grupos->name = "default";

    grupos->numtriangles = this->num_triangles;
    GLuint tri[this->num_triangles];
    for (int i = 0; i < this->num_triangles; i++)
	{
		tri[i] = i;
	}
    grupos->triangles = tri;
    grupos->next = NULL;

    this->model->groups = grupos;

    glmFacetNormals(this->model);
	glmVertexNormals(this->model, 90);
	glmWriteOBJ(this->model, path_name, GLM_SMOOTH);
}

void ObjMaker::create_triangle(int tri_index_a, int tri_index_b, int tri_index_c, int normal){
    GLMtriangle triangle;
    int triangle_input[] = {tri_index_a, tri_index_b, tri_index_c};
    
    for (int i = 0; i < 3; i++)
    {
        triangle.vindices[i] = triangle_input[i];
        triangle.nindices[i] = normal;
        triangle.tindices[i] = 0;
    }
    
    triangle.findex = 0;
    
    this->triangles_list[triangles_list_index++] = triangle;
}