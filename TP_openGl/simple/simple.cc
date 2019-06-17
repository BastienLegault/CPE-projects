// simple.cc

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "gl-utils.h"

GLuint vao; // Un V.A.O unique pour notre scène simple
GLuint vbo; // Un seul VBO pour le début (on pourra en ajouter ensuite)
GLuint vboi; // Le VBO pour les indices
GLuint program; // Le programme formé des deux shaders

// Ces variables pourront être utilisées pour animer nos objets
GLfloat angle1 = 0;
GLfloat angle2 = 0;

// Une structure contenant trois entiers pour simplifier des écritures :
struct vec3
{
  float x, y, z;
};

struct Vertex
{
  vec3 position ;
  vec3 color ;
};

/*---------------------------------------------------------------------------*\
 * init                                                                      *
\*---------------------------------------------------------------------------*/
static void init()
{
  glClearColor(0,0,0, 0); PRINT_OPENGL_ERROR();

  glEnable(GL_DEPTH_TEST); PRINT_OPENGL_ERROR();

  // Création de l'ensemble des shaders
  program = create_shader("shader.vert", "shader.frag", {"position","color"});

  // V.A.O obligatoire depuis 3.2 strict
  glGenVertexArrays(1, &vao); PRINT_OPENGL_ERROR();
  glBindVertexArray(vao);     PRINT_OPENGL_ERROR();

  vec3 position[] = { { .7,.5,0.5 }, { -.2,0,0.5 }, { .7,-.5,0.5 }, { -.7,.5,0 }, { -.7,-.5,0 }, {.3,.5,0 }, {.3,-.5,0 }};
  vec3 colors [] = { {1 ,0 ,0} , {0 ,1 ,0} , {0 ,0 ,1} };
 /* GLfloat vertices_c [] = { -.7,.5,0,     1. ,0. ,0.,
                         .2,0,0,       0. ,1. ,0.,
                         -.7,-.5,0,    0. ,0.,1.};
  */

  Vertex v0 = {position[0],colors[0]};
  Vertex v1 = {position[1],colors[1]};
  Vertex v2 = {position[2],colors[2]};
  Vertex v3 = {position[3],colors[0]};
  Vertex v4 = {position[4],colors[1]};
  Vertex v5 = {position[5],colors[2]};
  Vertex v6 = {position[6],{1,1,1}};

  Vertex vertices [] = {v0,v1,v2,v3,v4,v5,v6};
  // Modifier des trucs ici...
  // Création du/des VBO :
  glGenBuffers(1, &vbo); PRINT_OPENGL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER, vbo); PRINT_OPENGL_ERROR();
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW); PRINT_OPENGL_ERROR();
  glEnableVertexAttribArray(0); PRINT_OPENGL_ERROR();
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 6*sizeof(float), BUFFER_OFFSET(0)); PRINT_OPENGL_ERROR();

  glEnableVertexAttribArray(1); PRINT_OPENGL_ERROR();
  glVertexAttribPointer(1, 3, GL_FLOAT, false, 6*sizeof(float), (void*)(3 * sizeof(float))); PRINT_OPENGL_ERROR();


  GLushort indices [] = {0,1,2,   3,4,5,   4,5,6};
  glGenBuffers(1, &vboi); PRINT_OPENGL_ERROR();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboi); PRINT_OPENGL_ERROR();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW); PRINT_OPENGL_ERROR();






}

/*---------------------------------------------------------------------------*\
 * display_callback                                                          *
\*---------------------------------------------------------------------------*/
static void display_callback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); PRINT_OPENGL_ERROR();

  // Modifier des trucs ici...
  //glDrawArrays(GL_TRIANGLES, 0, 9); PRINT_OPENGL_ERROR();
  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, nullptr );

  glutSwapBuffers();
}

/*---------------------------------------------------------------------------*\
 * special_callback                                                          *
\*---------------------------------------------------------------------------*/
static void special_callback(int key, int, int)
{ // Gestion des touches "spéciales"
  switch (key)
    {
    case GLUT_KEY_RIGHT:
      angle1 += 5.f;
      break;
    case GLUT_KEY_LEFT:
      angle1 -= 5.f;
      break;
    case GLUT_KEY_UP:
      angle2 += 5.f;
      break;
    case GLUT_KEY_DOWN:
      angle2 -= 5.f;
      break;
    }
  glutPostRedisplay();
}

/*****************************************************************************\
 * main                                                                      *
\*****************************************************************************/
int main(int argc, char** argv)
{

  // Création du contexte :
  glutInitContextVersion(3, 3);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Simple");
  glewExperimental=true;
  glewInit();glGetError();
  init();
  glutDisplayFunc(display_callback);
  glutSpecialFunc(special_callback);

  glutMainLoop();
}

