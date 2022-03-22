/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>
#include "glm.h"
#include <stdio.h>
#include <vector>

GLfloat light_diffuse[] = {1.0, 1.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLfloat faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */


/*GLfloat vert[] = {1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, -1.0, 1.0, -1.0, -1.0};
GLuint triangle_ind[] = {0,1,2,3,4,5,6,7,8,9,10,11};
GLMmodel cubo;
GLMgroup grupo;*/
GLMtriangle triangles_list[200];
int triangles_list_index = 0;

void create_triangle(int tri_index_a, int tri_index_b, int tri_index_c, int normal){
	GLMtriangle tri;
	tri.vindices[0] = tri_index_a; 
	tri.vindices[1] = tri_index_b;
	tri.vindices[2] = tri_index_c;

	tri.nindices[0] = normal; 
	tri.nindices[1] = normal;
	tri.nindices[2] = normal;

	tri.tindices[0] = 0; 
	tri.tindices[1] = 0;
	tri.tindices[2] = 0;

	tri.findex = 0;
	triangles_list[triangles_list_index++] = tri;
	
	return;
}

void print_model(GLMmodel* modelo){
	printf("Nome do arquivo: %s\n", modelo->pathname);
	printf("Nome do material: %s\n", modelo->mtllibname);

	printf("Vertices: %d\n", modelo->numvertices);
	for (int i = 0; i < modelo->numvertices; i++)
	{
		printf("%f\n", modelo->vertices[i]);
	}

	printf("Normais: %d\n", modelo->numnormals);
	for (int i = 0; i < modelo->numnormals; i++)
	{
		printf("%f\n", modelo->normals[i]);
	}

	printf("Numero de TexCoords: %d\n", modelo->numtexcoords);
	for (int i = 0; i < modelo->numtexcoords; i++)
	{
		printf("%f\n", modelo->texcoords[i]);
	}

	printf("Numero de FacetNorms: %d\n", modelo->numfacetnorms);
	for (int i = 0; i < modelo->numfacetnorms; i++)
	{
		printf("%f\n", modelo->facetnorms[i]);
	}

	printf("Triangulos: %d\n", modelo->numtriangles);
	for (int i = 0; i < modelo->numtriangles; i++)
	{
		printf("f %d//%d//%d//%d %d//%d//%d//%d %d//%d//%d//%d\n",
			modelo->triangles[i].vindices[0],
			modelo->triangles[i].nindices[0],
			modelo->triangles[i].tindices[0],
			modelo->triangles[i].findex,
			
			modelo->triangles[i].vindices[1],
			modelo->triangles[i].nindices[1],
			modelo->triangles[i].tindices[1],
			modelo->triangles[i].findex,
			
			modelo->triangles[i].vindices[2],
			modelo->triangles[i].nindices[2],
			modelo->triangles[i].tindices[2],
			modelo->triangles[i].findex
		);
	}

	printf("Numero de grupos: %d\n", modelo->numgroups);
	printf("Nome do grupo: %s\n", modelo->groups->name);
	printf("Numero de triangulos do grupo: %d\n", modelo->groups->numtriangles);
	for (int i = 0; i < modelo->groups->numtriangles; i++)
	{
		printf("%d\n", modelo->groups->triangles[i]);
	}
	printf("Material do grupo: %d\n", modelo->groups->material);

	/*printf("Nome do grupo: %s\n", modelo->groups->next->name);
	printf("Numero de triangulos do grupo: %d\n", modelo->groups->next->numtriangles);
	for (int i = 0; i < modelo->groups->next->numtriangles; i++)
	{
		printf("%d\n", modelo->groups->next->triangles[i]);
	}
	printf("Material do grupo: %d\n", modelo->groups->next->material);*/


}

void create_obj(char* path_name, char* name, int nVertices, float vertices_array[], int nNormals, int ntriangles){
	printf("create_obj()\n");
	GLMmodel modelo;

	modelo.pathname = path_name;
	modelo.mtllibname = nullptr;

	modelo.numvertices = nVertices;
	int size = (nVertices*3)+3;
	GLfloat vert[size];
	for (int i = 3, j=0; i < size; i++, j++)
	{
		vert[i] = vertices_array[j];
	}
	modelo.vertices = vert;

	modelo.numnormals = nNormals;
	modelo.normals = nullptr;
	/*GLfloat norm[nNormals];
	for (int i = 0; i < nNormals; i++)
	{
		norm[i] = 0;
	}
	modelo.normals = norm;*/


	modelo.numtexcoords = 0;

	modelo.numfacetnorms = 0;

	modelo.numtriangles = ntriangles;
	modelo.triangles = triangles_list;

	modelo.nummaterials = 0;

	modelo.numgroups = 1;
	
	GLMgroup grupos[1];
	grupos->name = "default";

	grupos->numtriangles = ntriangles;
	GLuint tri[ntriangles];
	for (int i = 0; i < ntriangles; i++)
	{
		tri[i] = i;
	}
	grupos->triangles = tri;

	grupos->next = nullptr;

	modelo.groups = grupos;

	printf("indo writeOBJ\n");
	glmFacetNormals(&modelo);
	glmVertexNormals(&modelo, 90);
	glmWriteOBJ(&modelo, path_name, GLM_SMOOTH);
	print_model(&modelo);

	return;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   	glLoadIdentity();                 // Reset the model-view matrix
   	glTranslatef(0.5f, 0.0f, -7.0f);  // Move right and into the screen
	
	glRotatef(20, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		// Top face (y = 1.0f)
		// Define vertices in counter-clockwise (CCW) order with normal pointing out
		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		glVertex3f( 1.0f, 1.0f, -1.0f); //1
		glVertex3f(-1.0f, 1.0f, -1.0f); //2
		glVertex3f(-1.0f, 1.0f,  1.0f); //3
		glVertex3f( 1.0f, 1.0f,  1.0f); //4
		
		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 0.5f, 0.0f);     // Orange
		glVertex3f( 1.0f, -1.0f,  1.0f); //5
		glVertex3f(-1.0f, -1.0f,  1.0f); //6
		glVertex3f(-1.0f, -1.0f, -1.0f); //7
		glVertex3f( 1.0f, -1.0f, -1.0f); //8
	
		// Front face  (z = 1.0f)
		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f( 1.0f,  1.0f, 1.0f); // 4
		glVertex3f(-1.0f,  1.0f, 1.0f); // 3
		glVertex3f(-1.0f, -1.0f, 1.0f); // 6
		glVertex3f( 1.0f, -1.0f, 1.0f); // 5
	
		// Back face (z = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f( 1.0f, -1.0f, -1.0f); // 8
		glVertex3f(-1.0f, -1.0f, -1.0f); // 7
		glVertex3f(-1.0f,  1.0f, -1.0f); // 2
		glVertex3f( 1.0f,  1.0f, -1.0f); // 1
	
		// Left face (x = -1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(-1.0f,  1.0f,  1.0f); //3
		glVertex3f(-1.0f,  1.0f, -1.0f); //2
		glVertex3f(-1.0f, -1.0f, -1.0f); //7
		glVertex3f(-1.0f, -1.0f,  1.0f); //6
	
		// Right face (x = 1.0f)
		glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
		glVertex3f(1.0f,  1.0f, -1.0f); //1
		glVertex3f(1.0f,  1.0f,  1.0f); //4
		glVertex3f(1.0f, -1.0f,  1.0f); //5
		glVertex3f(1.0f, -1.0f, -1.0f); //8
	glEnd();  // End of drawing color-cube

	glutSwapBuffers();
}

void init(void)
{
	/* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
		0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		0.0, 1.0, 0.);      /* up is in positive Y direction */

	/* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("red 3D lighted cube");
	glutDisplayFunc(display);
	init();

	/*GLMmodel* cuboso = glmReadOBJ("ccc.obj");
	print_model(cuboso);
	glmWriteOBJ(cuboso, "eee.obj", GLM_SMOOTH);*/
	
	
	create_triangle(1,2,3,1);
	create_triangle(1,3,4,1);

	create_triangle(5,6,7,2);
	create_triangle(5,7,8,2);

	create_triangle(4,3,6,3);
	create_triangle(4,6,5,3);

	create_triangle(8,7,2,4);
	create_triangle(8,2,1,4);

	create_triangle(3,2,7,5);
	create_triangle(3,7,6,5);

	create_triangle(1,4,5,6);
	create_triangle(1,5,8,6);

	float vertices[] = {1,1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1};
	create_obj("cube.obj", "cube", 8, vertices, 6, 12);

	glutMainLoop();

	return 0;             /* ANSI C requires main to return int. */
}