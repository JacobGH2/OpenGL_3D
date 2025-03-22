//#include"main.h"
#include"menu.h"
#include"display.h"
#include"util.h"

//glutMainLoop never return;
int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Assignment 3");
    
    setup();
        
    // initializing callbacks
     glutReshapeFunc(reshape);
     glutDisplayFunc(display);
     glutMouseFunc(mouse);
     glutMotionFunc(motion);
     glutKeyboardFunc(processKeys);
     
     glutSpecialFunc(specialKey); //register a special keyboard function.
    //Creates Menu on Right Click
     CreateMenu();

     glutMainLoop();
     return 0;

}
