// main.cc

#include <iostream>
#include <cstdlib>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "gl-utils.h"
#include "matrix.h"
#include "image.h"

const int NB_PARTICULES = 500;

enum
{
  POSITION0,
  POSITION1,
  VITESSE0,
  VITESSE1
};

static GLuint query;
static GLuint buffers[4];

static GLuint  program_tf;
static GLuint  program;

static void init()
{
  vec3 positions[NB_PARTICULES];
  vec3 vitesses[NB_PARTICULES];
  const char *varyings[1] = { "v_position" };

  program_tf = read_shader("data/tf.vert", "data/tf.frag");
  glTransformFeedbackVaryings(program_tf, 1, varyings, GL_SEPARATE_ATTRIBS); PRINT_OPENGL_ERROR();
  glBindAttribLocation(program_tf, 0, "position");                           PRINT_OPENGL_ERROR();
  glBindAttribLocation(program_tf, 1, "vitesse");                            PRINT_OPENGL_ERROR();
  glLinkProgram(program_tf);                                                 PRINT_OPENGL_ERROR();

  program = read_shader("data/shader.vert", "data/shader.frag");
  glBindAttribLocation(program, 0, "position"); PRINT_OPENGL_ERROR();
  glLinkProgram(program);                       PRINT_OPENGL_ERROR();

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0); PRINT_OPENGL_ERROR();
  // L'objet query
  glGenQueries(1, &query);

  for (int i = 0; i < NB_PARTICULES; i++)
  {
    positions[i] = vec3(-0.9,1.-2*double(rand())/RAND_MAX,double(rand())/RAND_MAX);
    vitesses[i]  = vec3(double(rand())/RAND_MAX, 0, 0); 
  }

  // Les quatre VBO : deux pour les positions, deux pour les vitesses
  glGenBuffers(4, buffers);                                                      PRINT_OPENGL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION0]);                             PRINT_OPENGL_ERROR();
  glBufferData(GL_ARRAY_BUFFER, sizeof positions, positions, GL_STATIC_DRAW);    PRINT_OPENGL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION1]);                             PRINT_OPENGL_ERROR();
  glBufferData(GL_ARRAY_BUFFER, sizeof positions, positions, GL_STREAM_DRAW);    PRINT_OPENGL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER, buffers[VITESSE0]);                              PRINT_OPENGL_ERROR();
  glBufferData(GL_ARRAY_BUFFER, sizeof vitesses, vitesses, GL_STREAM_DRAW);      PRINT_OPENGL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER, buffers[VITESSE1]);                              PRINT_OPENGL_ERROR();
  glBufferData(GL_ARRAY_BUFFER, sizeof vitesses, vitesses, GL_STREAM_DRAW);      PRINT_OPENGL_ERROR();

  glPointSize(5);                                                                PRINT_OPENGL_ERROR();
  glClearColor(0.0, 0.0, 0.3, 1.0); PRINT_OPENGL_ERROR();                        PRINT_OPENGL_ERROR();
}

static GLuint update_particles()
{
  GLuint written_particles;
  glEnable(GL_RASTERIZER_DISCARD);                                               PRINT_OPENGL_ERROR();
  glUseProgram(program_tf);                                                      PRINT_OPENGL_ERROR();
  // Préparation pour les positions
  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffers[POSITION1]);         PRINT_OPENGL_ERROR();
  glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION0]);                             PRINT_OPENGL_ERROR();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);                         PRINT_OPENGL_ERROR();
  // Préparation pour les vitesses
  // ...
  glBindBuffer(GL_ARRAY_BUFFER, buffers[VITESSE0]);                              PRINT_OPENGL_ERROR();
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);                         PRINT_OPENGL_ERROR();
  // C'est parti !
  glEnableVertexAttribArray(1);                                                  PRINT_OPENGL_ERROR();
  glBeginTransformFeedback(GL_POINTS);                                           PRINT_OPENGL_ERROR();
  glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);                 PRINT_OPENGL_ERROR();
  glDrawArrays(GL_POINTS, 0, NB_PARTICULES);                                     PRINT_OPENGL_ERROR();
  glEndTransformFeedback();                                                      PRINT_OPENGL_ERROR();
  glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);                          PRINT_OPENGL_ERROR();
  glGetQueryObjectuiv(query, GL_QUERY_RESULT, &written_particles);               PRINT_OPENGL_ERROR();
  glDisableVertexAttribArray(1);                                                 PRINT_OPENGL_ERROR();
 
  std::swap(buffers[POSITION0], buffers[POSITION1]);
  glDisable(GL_RASTERIZER_DISCARD);                                              PRINT_OPENGL_ERROR();

  return written_particles;
}

/*****************************************************************************\
 * display_callback                                                          *
\*****************************************************************************/
static void display_callback()
{
  matrix projection;
  GLuint count = update_particles();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                PRINT_OPENGL_ERROR();
  glUseProgram(program);                                                             PRINT_OPENGL_ERROR();
  glUniformMatrix4fv(get_uni_loc(program, "projection"), 1, GL_FALSE, projection.m); PRINT_OPENGL_ERROR();


  glBindBuffer(GL_ARRAY_BUFFER, buffers[POSITION0]);     PRINT_OPENGL_ERROR();
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); PRINT_OPENGL_ERROR();
  glDrawArrays(GL_POINTS, 0, count);                     PRINT_OPENGL_ERROR();

  glutSwapBuffers();
}

/*****************************************************************************\
 * keyboard_callback                                                         *
\*****************************************************************************/
static void keyboard_callback(unsigned char key, int, int)
{
  switch (key)
  {
    case 'q':
    case 'Q':
    case 27:
      exit(0);
  }
}

/*****************************************************************************\
 * special_callback                                                          *
\*****************************************************************************/
static void special_callback(int key, int,int)
{
  switch (key)
  {
    case GLUT_KEY_UP:
//      angle1 += 0.1f;
      break;
    case GLUT_KEY_DOWN:
//      angle1 -= 0.1f;
      break;
    case GLUT_KEY_LEFT:
//      angle2 += 0.1f;
      break;
    case GLUT_KEY_RIGHT:
//      angle2 -= 0.1f;
      break;
  }
  glutPostRedisplay();
}

/*****************************************************************************\
 * timer_callback                                                            *
\*****************************************************************************/
static void timer_callback(int)
{
  glutTimerFunc(25, timer_callback, 0);
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInitContextVersion(3, 3);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Transform feedback");
  glutDisplayFunc(display_callback);
  glutKeyboardFunc(keyboard_callback);
  glutSpecialFunc(special_callback);
  glutTimerFunc(25, timer_callback, 0);

  glewExperimental=true;
  glewInit(); PRINT_OPENGL_ERROR();
  init();

  glutMainLoop();

  return 0;
}

