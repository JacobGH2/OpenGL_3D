#include"display.h"
#include"util.h"

//#define NDEBUG  // used to disabled all assert.
GLsizei width, height;


double m_xtheta=0;
double m_ytheta=0;
double m_ztheta=0;
double m_slide=40;

double theta_all = 0;

double tr_lr = 0;
double tr_ud = 0;
double tr_io = 0;

void setup()
{
    glClearColor(0, 0, 0, 1.0); // *should* display black background
}


void reshape( int w, int h ){
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); // set to size of window
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //gluOrtho2D( 0.0, (float)w, 0.0, (float)h );

    glOrtho( 0, w, h, 0, -1, 1 );
    width = w;  // records width globally
    height = h; // records height globally

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void display(){
   // glClear(GL_COLOR_BUFFER_BIT); // clear window
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );

   glColor3f(0,1,0);
   glLineWidth(1);
   glEnable(GL_DEPTH_TEST);

   glViewport(width/2.0, 0, width/2.0, height/2.0); //V1
   {
     
      projection(width/2.0, height/2.0, 1);
      gluLookAt(0, 0, m_slide, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
     // glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
      glPushMatrix();
      glRotatef(m_xtheta, 1,0,0);
      glRotatef(m_ytheta, 0,1,0);
      glRotatef(m_ztheta, 0,0,1);
      RenderGLScene(5, 5, 30);
      glPopMatrix();
   }
   glViewport(width/2.0, height/2.0, width/2.0, height/2.0); //V4
   {
        projection(width/2.0, height/2.0, 1);
        gluLookAt(0, 0, 100, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glPushMatrix();
        RenderLeverScene();
        glPopMatrix();
   }
   glViewport(0, height/2.0, width/2.0, height/2.0); //V3
   {
        projection(width/2.0, height/2.0, 1);
        gluLookAt(-100, 0, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glPushMatrix();
        RenderLeverScene();
        glPopMatrix();
   }
   glViewport(0, 0, width/2.0, height/2.0); //V2
   {
        projection(width/2.0, height/2.0, 1);
        gluLookAt(0, 100, 0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
        glPushMatrix();
        RenderLeverScene();
        glPopMatrix();
   }

   glutSwapBuffers(); // display newly drawn image in window
}


void projection(int width, int height, int perspectiveORortho){
  float ratio = (float)width/height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (perspectiveORortho)
      gluPerspective(60, ratio, 1, 256);
  else 
      glOrtho(-ratio, ratio, -ratio, ratio, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
}


void RenderGLScene(int base_radius, int top_radius, int height){
  // draw a cylinder or a sphere, 
  // you will draw more objects in this function
  GLUquadricObj* quadObj = gluNewQuadric ();
  gluQuadricDrawStyle (quadObj, GLU_LINE);
  gluCylinder(quadObj, base_radius, top_radius, height, 20, 10);       //draw a cone shape cylinder
  DrawGround(-10.0);  //draw ground lines for reference 
  gluDeleteQuadric(quadObj);
  glFlush();
}

void drawCylinder(int base_radius, int top_radius, int height) {
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
   
    gluCylinder(quadObj, base_radius, top_radius, height, 20, 10);       //draw a cone shape cylinder
    gluDeleteQuadric(quadObj);
}

void RenderLeverScene(){
    // draw a cylinder or a sphere, 
    // you will draw more objects in this function
    DrawGround(-40.0);

    glPushMatrix();
    glRotated(theta_all, 0, 1, 0);
    glPushMatrix(); // -- main cylinder

        glRotatef(90.0, 1,0,0);
        
        drawCylinder(4, 4, 40);
    glPopMatrix();

    // ----------------------- across cylinder
    glPushMatrix();

        glTranslated(-20, 0, 0);
        glRotatef(90.0, 0,1,0);
        

        drawCylinder(4, 4, 40);
    glPopMatrix();
    // ----------------------- left sphere
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3d(255, 0, 0);

        glTranslated(-20, 0, 0);
        glutSolidSphere(6, 20, 20);

        glColor3d(0, 255, 0);
        glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();
    // ----------------------- right sphere
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3d(0, 0, 255);

        glTranslated(20, 0, 0);
        glutSolidSphere(6, 20, 20);

        glColor3d(0, 255, 0);
        glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();

    // ------------------------------------------- S4 rotation  
    glPushMatrix();
    glRotated(-1 * theta_all, 1, 0, 0);
    // ----------------------- left cone
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3d(1, .3, .5);

        glTranslated(-20, 0, 0);
        glRotated(-90, 1, 0, 0);
        glTranslated(0, 0, -25);
        glutSolidCone(5, 30, 10, 20);

        glColor3d(0, 1, 0);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    
    // ----------------------- left cone sphere
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3d(0, 0, 1);

        glTranslated(-20, -25, 0);
        glutSolidSphere(8, 20, 20);

        glColor3d(0, 255, 0);
        glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();

    glPopMatrix();

    // ------------------------------------------- S5 rotation
    glPushMatrix();
    glRotated(theta_all, 1, 0, 0);
    // ----------------------- right cone
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3d(1, .3, .5);

        glTranslated(20, 0, 0);
        glRotated(-90, 1, 0, 0);
        glTranslated(0, 0, -25);
        glutSolidCone(5, 30, 10, 20);

        glColor3d(0, 1, 0);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

   
    // ----------------------- right cone sphere
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3d(1, 0, 0);

        glTranslated(20, -25, 0);
        glutSolidSphere(8, 20, 20);

        glColor3d(0, 255, 0);
        glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();

    glPopMatrix();
    // ----------------------- center sphere
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3d(1, .5, 0);

        glutSolidSphere(6, 20, 20);

        glColor3d(0, 255, 0);
        glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();
    glPopMatrix();

    glFlush();
}


void DrawGround(double height){
  glBegin(GL_LINES);

  for(float i =-1; i<=1; )
   {
       glVertex3f(i*100.f, height, -100.f);
       glVertex3f(i*100.f, height, 100.f);
       i+=0.1;
   }
  for(float j =-1; j<=1; )
    {
       glVertex3f(-100.f, height, j*100.f);
       glVertex3f(100.f, height, j*100.f);
       j+=0.1;
    }
  glEnd();
}

void RollUp(float n){
  m_ztheta+=n;
  if(m_ztheta > 360) m_ztheta=-360;
}
void RollDown(float n){
  m_ztheta-=n;
  if(m_ztheta < -360) m_ztheta=360;
}
void PitchUp(float n){
  m_ytheta+=n;
  if(m_ytheta > 360) m_ytheta=-360;
}
void PitchDown(float n){
  m_ytheta-=n;
  if(m_ytheta < -360) m_ytheta=360;
}
void YawUp(float n){
  m_xtheta+=n;
  if(m_xtheta > 360) m_xtheta=-360;
}
void YawDown(float n){
  m_xtheta-=n;
  if(m_xtheta < -360) m_xtheta=360;
}
void SlideUp(float n){
  m_slide+=n;
}
void SlideDown(float n ){
  m_slide-=n;
}
void incThetaAll() {
    theta_all += 10;
    if (theta_all > 360) theta_all = 10;
}
void decThetaAll() {
    theta_all -= 10;
    if (theta_all < 0) theta_all = 350;
}
void MoveLeft() {tr_lr += 5;}
void MoveRight() {tr_lr -= 5;}
void MoveUp() {tr_ud += 5;}
void MoveDown() {tr_ud -= 5;}
void MoveIn() {tr_io += 5;} // change if needed
void MoveOut() {tr_io -= 5;}
