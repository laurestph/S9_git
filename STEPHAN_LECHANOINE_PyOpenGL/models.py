# from math import pi,sin,cos
try :
  from OpenGL.GLUT import *
  from OpenGL.GL import *
  from OpenGL.GLU import *
except:
  print ("Error: PyOpenGL not installed properly !!")
  sys.exit()

def create_base(size) :
  glutSolidCube(size)

def create_sphere(radius,longitude=10,latitude=20) :
  params=gluNewQuadric()
  gluQuadricDrawStyle(params,GLU_FILL)
  gluQuadricTexture(params,GL_TRUE)
  gluSphere(params,radius,longitude,latitude)
  gluDeleteQuadric(params)

def create_cylinder(base,top,height,slices=10,stacks=5) :
  params=gluNewQuadric()
  gluQuadricDrawStyle(params,GLU_FILL)
  gluQuadricTexture(params,GL_TRUE)
  gluCylinder(params,base,top,height,slices,stacks)
  gluDeleteQuadric(params)

def create_disk(inner,outer,slices=10,loops=5) :
  params=gluNewQuadric()
  gluQuadricDrawStyle(params,GLU_FILL)
  gluQuadricTexture(params,GL_TRUE)
  gluDisk(params,inner,outer,slices,loops)
  gluDeleteQuadric(params)

def create_stick(base,top,height,slices=10,stacks=5) :
  glPushMatrix()
  glRotatef(180,0,1,0)
  create_disk(0,base,slices,stacks)
  glPopMatrix()
  create_cylinder(base,top,height,slices,stacks)
  glPushMatrix()
  glTranslatef(0,0,height)
  create_disk(0,base,slices,stacks)
  glPopMatrix()

def create_axe(size,slices=10,stacks=5) :
  glPushMatrix()
  glColor3f(1.0,0.0,0.0)
  glRotatef(180,0,1,0)
  create_disk(0,size,slices,stacks)
  glPopMatrix()
  create_cylinder(size,size,12*size,slices,stacks)
  glPushMatrix()
  glTranslatef(0,0,12*size)
  create_cone(size*1.5,4*size,slices,stacks)
  glPopMatrix()

def create_cone(base,height,slices=10,stacks=5) :
  glPushMatrix()
  glRotatef(180,0,1,0)
  create_disk(0,base,slices,stacks)
  glPopMatrix()
  create_cylinder(base,0,height,slices,stacks)


def world_coordinate_system(size) :
  glBegin(GL_LINES)
  glColor3ub(255,255,255)
  glVertex2f(0,0)
  glVertex2f(0,size)
  glVertex2f(0,0)
  glVertex2f(size,0)
  glVertex2f(0,0)
  glVertex3f(0,0,size)
  glEnd()

def create_floor(size,tiles=10) :
  tile_size=size/tiles
  for i in range(10+1) :
    for j in range(10+1) :
        glPushMatrix()
#        glTranslatef(-size/2.0+tile_size*i,-1.0,-size/2.0+tile_size*j)
        glTranslatef(-size/2.0+tile_size*i,0.0,-size/2.0+tile_size*j)
        if (i+j)%2 == 0 :
            glColor3f(1.0,1.0,1.0)
            glRotatef(-90,1,0,0)
            glRectf(-tile_size/2.0, -tile_size/2.0, tile_size/2.0, tile_size/2.0)
        else :
            glColor3f(0.0,0.0,0.0)
            glRotatef(90,1,0,0)
            glRectf(-tile_size/2.0, -tile_size/2.0, tile_size/2.0, tile_size/2.0)
        glPopMatrix()

def square(size) :
# face avant : sommets de couleurs RGBW
  glBegin(GL_POLYGON)
  glColor3f(1.0,0.0,0.0)   # Red 
  glVertex2f(-size,-size)
  glColor3f(0.0,1.0,0.0)   # Green
  glVertex2f(size,-size)
  glColor3f(0.0,0.0,1.0)   # Blue
  glVertex2f(size,size)
  glColor3f(1.0,1.0,1.0)   #  White
  glVertex2f(-size,size)
  glEnd()
#face arriere : couleur uniforme White
  glBegin(GL_POLYGON)
  glVertex2f(-size,-size)
  glVertex2f(-size,size)
  glVertex2f(size,size)
  glVertex2f(size,-size)
  glEnd()
