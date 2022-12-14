/********************************************************/
/*                     quadric.c                        */
/********************************************************/
/*  Premiers pas avec OpenGL.                           */
/* Objectif : creer une quadrique : sphere              */
/********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

static float size=0.5;
static float theta_y=0.0;

void gl_init(void);
void glut_init(int argc,char **argv);
void glut_event(void);

void display(void);
void keyboard(unsigned char key,int x,int y);
void reshape(int width, int height);

void wcs(float size);
void carre(float size);
void cube(float size);


void glut_init(int argc,char **argv)
{
 glutInit(&argc,argv);
// glutInitDisplayMode(GLUT_RGB);
 glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
 glutInitWindowPosition(200,200);
 glutInitWindowSize(250,250);
 glutCreateWindow(argv[0]);
}

void glut_event(void)
{
 glutDisplayFunc(display);
 glutKeyboardFunc(keyboard);
 glutReshapeFunc(reshape);
}

void wcs(float size) {
 glBegin(GL_LINES);
 glColor3f(1.0,1.0,1.0);
 glVertex2f(0.0,0.0);
 glVertex2f(0.0,1.5*size);
 glVertex2f(0.0,0.0);
 glVertex2f(1.5*size,0.0);
 glVertex2f(0.0,0.0);
 glVertex3f(0.0,0.0,1.5*size);
 glEnd();
}

void world_coordinate_system(int size) {
  glBegin(GL_LINES);
  glColor3ub(255,255,255);
  glVertex2i(0,0);
  glVertex2i(0,size);
  glVertex2i(0,0);
  glVertex2i(size,0);
  glVertex2i(0,0);
  glVertex3i(0,0,size);
  glEnd();
}

void create_sphere(GLfloat radius, GLint longitude,GLint latitude) {

	GLUquadric* params = gluNewQuadric();
//	gluQuadricDrawStyle(params,GLU_FILL);
	gluQuadricDrawStyle(params,GLU_LINE);
  gluQuadricTexture(params,GL_TRUE);
  gluSphere(params,radius,longitude,latitude);
  gluDeleteQuadric(params);
}

void create_cylinder(GLdouble base, GLdouble top, GLdouble height, GLint slices,GLint stacks)
{
  GLUquadric* params = gluNewQuadric();
  gluQuadricDrawStyle(params,GLU_LINE);
  gluQuadricTexture(params,GL_TRUE);
  gluCylinder(params,base,top,height,slices,stacks);
  gluDeleteQuadric(params);
}


void create_disk(GLdouble inner, GLdouble outer, GLint slices,  GLint loops)
{
  GLUquadric* params = gluNewQuadric();
  gluQuadricDrawStyle(params,GLU_LINE);
  gluQuadricTexture(params,GL_TRUE);
  gluDisk(params,inner,outer,slices,loops);
  gluDeleteQuadric(params);
}

void gl_init(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glEnable(GL_CULL_FACE);
 glClearColor(0.0,0.0,0.0,0.0);
 glColor3f(1.0,1.0,1.0);
 glPointSize(2.0);
}

void display()
{
 gl_init();
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glEnable(GL_CULL_FACE);
// glCullFace (GL_BACK);
// glCullFace (GL_FRONT);
// glFrontFace(GL_CCW);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
// gluLookAt(0,0,2,0,0,0,0,1,0);
gluLookAt(4,3,2,0,0,0,0,1,0);
// glutWireCube(1);
wcs(size+1);
glRotatef(theta_y,0,1,0);
create_sphere(size,10,5);
//create_cylinder(size,size*0.5,size,10,5);
//create_disk(size*0.5,size,10,5);
glutSwapBuffers();
}

void reshape(int width, int height) {
  glViewport(0,0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 10.0);
  glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key,int x,int y)
{
 switch (key) 
 {
  case 'h': 
   printf("----------------------------------------\n"); 
   printf("Documentation interaction  : Nom-Prenom \n"); 
   printf("----------------------------------------\n"); 
   printf("h : afficher cette aide \n"); 
   printf("f : afficher les facettes \n"); 
   printf("e : afficher les aretes \n"); 
   printf("v : afficher les sommets \n"); 
   printf("c/C : afficher les faces CW/CCW \n"); 
   printf("s/S : redimensionner l'objet \n"); 
   printf("y/Y : tourner l'objet autour de l'axe Oy\n"); 
   printf("x : sortie (exit) \n"); 
  case 'f': 
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   break;
  case 'e':
   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   break;
  case 'v' :
   glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
   break;
  case 'c' :// glutWireCube(1);

   glFrontFace(GL_CW);
   break;
  case 'C' : 
   glFrontFace(GL_CCW);
   break;
  case 's' : 
   size-=0.01;
   break;
  case 'S' : 
   size+=0.01;
   break;
  case 'y' : 
   theta_y-=1.0;
   break;
  case 'Y' : 
   theta_y+=1.0;
   break;
  case 'x' :
   exit(0);
  default :
   break;
 }
 glutPostRedisplay();
}

int main(int argc,char **argv)
{
 glut_init(argc,argv);
 glut_event();
 glutMainLoop();
 return 0;
}


