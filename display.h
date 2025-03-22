#define PI 3.1415926


void setup();
void reshape( int w, int h );
void display();
void projection(int width, int height, int perspectiveORortho);
void RenderGLScene(int base_raidus, int top_radius, int height);
void DrawGround(double);

// setting the rotation.
void RollUp(float n);
void RollDown(float n);
void PitchUp(float n);
void PitchDown(float n);
void YawUp(float n);
void YawDown(float n);
void SlideUp(float n);
void SlideDown(float n );
void RenderLeverScene();
void drawCylinder(int, int, int);
void incThetaAll();
void decThetaAll();
void MoveLeft();
void MoveRight(); 
void MoveUp();
void MoveDown();
void MoveIn();
void MoveOut(); 

