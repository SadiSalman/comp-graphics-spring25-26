#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
const int W = 1000, H = 700;
const float PI = 3.14159f;
void drawCircle(float cx, float cy, float r, int segs = 70)
{
glBegin(GL_POLYGON);
for (int i = 0; i < segs; i++) {
float a = 2.0f * PI * i / segs;
glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
}
glEnd();
}
void drawCloud(float cx, float cy)
{
glColor3f(1.0f, 1.0f, 1.0f);
drawCircle(cx,     cy,     30);
drawCircle(cx-25,  cy-5,   25);
drawCircle(cx+25,  cy-5,   25);
drawCircle(cx,     cy+20,  20);
}
void drawWindow(float x1, float y1, float x2, float y2)
{
glColor3f(0.75f, 0.90f, 1.00f);
glBegin(GL_QUADS);
glVertex2f(x1,y1); glVertex2f(x2,y1);
glVertex2f(x2,y2); glVertex2f(x1,y2);
glEnd();
glColor3f(0.30f, 0.30f, 0.30f);
glBegin(GL_LINES);
float mx = (x1+x2)/2.0f, my = (y1+y2)/2.0f;
glVertex2f(mx, y1); glVertex2f(mx, y2);
glVertex2f(x1, my); glVertex2f(x2, my);
glVertex2f(x1,y1); glVertex2f(x2,y1);
glVertex2f(x2,y1); glVertex2f(x2,y2);
glVertex2f(x2,y2); glVertex2f(x1,y2);
glVertex2f(x1,y2); glVertex2f(x1,y1);
glEnd();
}
void drawHouse(float x, float y, float width, float height, float r, float g, float b)
{
float roofHeight = height * 0.4f;
glColor3f(r, g, b);
glBegin(GL_QUADS);
glVertex2f(x, y);
glVertex2f(x+width, y);
glVertex2f(x+width, y+height);
glVertex2f(x, y+height);
glEnd();
glColor3f(0.72f, 0.18f, 0.12f);
glBegin(GL_QUADS);
glVertex2f(x-10, y+height);
glVertex2f(x+width+10, y+height);
glVertex2f(x+width+10, y+height+roofHeight);
glVertex2f(x-10, y+height+roofHeight);
glEnd();
glColor3f(0.42f, 0.24f, 0.08f);
glBegin(GL_QUADS);
glVertex2f(x+width*0.7f, y+height+roofHeight);
glVertex2f(x+width*0.8f, y+height+roofHeight);
glVertex2f(x+width*0.8f, y+height+roofHeight+30);
glVertex2f(x+width*0.7f, y+height+roofHeight+30);
glEnd();
glColor3f(0.48f, 0.28f, 0.10f);
glBegin(GL_QUADS);
glVertex2f(x+width*0.4f, y);
glVertex2f(x+width*0.6f, y);
glVertex2f(x+width*0.6f, y+height*0.5f);
glVertex2f(x+width*0.4f, y+height*0.5f);
glEnd();
glColor3f(1.0f, 0.85f, 0.0f);
glPointSize(5.0f);
glBegin(GL_POINTS);
glVertex2f(x+width*0.58f, y+height*0.25f);
glEnd();
glPointSize(1.5f);
drawWindow(x+width*0.1f, y+height*0.6f, x+width*0.3f, y+height*0.9f);
drawWindow(x+width*0.7f, y+height*0.6f, x+width*0.9f, y+height*0.9f);
}
void drawTree(float x, float y, float trunkWidth, float trunkHeight)
{
glColor3f(0.42f, 0.25f, 0.08f);
glBegin(GL_QUADS);
glVertex2f(x, y);
glVertex2f(x+trunkWidth, y);
glVertex2f(x+trunkWidth, y+trunkHeight);
glVertex2f(x, y+trunkHeight);
glEnd();
float cx = x + trunkWidth/2.0f;
float cy = y + trunkHeight;
glColor3f(0.10f, 0.54f, 0.10f);
drawCircle(cx, cy+40, 40);
glColor3f(0.12f, 0.46f, 0.12f);
drawCircle(cx-30, cy+20, 30);
drawCircle(cx+30, cy+20, 30);
glColor3f(0.08f, 0.58f, 0.08f);
drawCircle(cx, cy, 28);
}
void drawRoad(float y, float height)
{
glColor3f(0.76f, 0.60f, 0.32f);
glBegin(GL_QUADS);
glVertex2f(0, y);
glVertex2f(W, y);
glVertex2f(W, y+height);
glVertex2f(0, y+height);
glEnd();
}

float birdOffset = 0.0f;

void drawBird(float x, float y, float size)
{
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_LINES);
glVertex2f(x, y+size);
glVertex2f(x+size, y);
glVertex2f(x+size, y);
glVertex2f(x+2*size, y+size);
glEnd();
}
void drawMountain(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)
{
glColor3f(r, g, b);
glBegin(GL_TRIANGLES);
glVertex2f(x1, y1);
glVertex2f(x2, y2);
glVertex2f(x3, y3);
glEnd();
}
void drawFence(float x, float y, float length, float height, int posts)
{
float spacing = length / (posts - 1);
glLineWidth(4.0f);
glColor3f(0.55f, 0.35f, 0.20f);
glBegin(GL_LINES);
glVertex2f(x, y + height*0.3f);
glVertex2f(x + length, y + height*0.3f);
glVertex2f(x, y + height*0.7f);
glVertex2f(x + length, y + height*0.7f);
glEnd();
glBegin(GL_LINES);
for (int i = 0; i < posts; i++)
{
float px = x + i * spacing;
glVertex2f(px, y);
glVertex2f(px, y + height);
}
glEnd();
}
void update(int value) {
    birdOffset += 2.0f;
    if (birdOffset > W)
        birdOffset = -100.0f;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}
float sunY = 520.0f;
float sunR = 1.0f, sunG = 0.92f, sunB = 0.0f;


float skyR = 0.53f, skyG = 0.81f, skyB = 0.98f;
void updateSun(int value) {
    sunY -= 0.5f; // move sun downward
    if (sunY < 200.0f) sunY = 520.0f; // reset after setting

    // Sun color transition
    if (sunY > 350.0f) { sunR = 1.0f; sunG = 0.92f; sunB = 0.0f; }       // bright yellow
    else if (sunY > 250.0f) { sunR = 1.0f; sunG = 0.5f; sunB = 0.0f; }   // orange
    else { sunR = 0.8f; sunG = 0.2f; sunB = 0.2f; }                      // reddish

    // Sky color transition
    if (sunY > 350.0f) { skyR = 0.53f; skyG = 0.81f; skyB = 0.98f; }     // daytime blue
    else if (sunY > 250.0f) { skyR = 0.85f; skyG = 0.65f; skyB = 0.45f; } // sunset orange
    else { skyR = 0.15f; skyG = 0.15f; skyB = 0.30f; }                   // evening dark blue

    glutPostRedisplay();
    glutTimerFunc(30, updateSun, 0);
}


void display()
{

    (GL_COLOR_BUFFER_BIT);
    glColor3f(skyR, skyG, skyB);
    glBegin(GL_QUADS);
    glVertex2f(0,185); glVertex2f(W,185);
    glVertex2f(W,H);   glVertex2f(0,H);
    glEnd();


    glColor3f(sunR, sunG, sunB);
    drawCircle(800.0f, sunY, 50.0f);

    glColor3f(sunR * 0.9f, sunG * 0.9f, sunB * 0.9f);
    glBegin(GL_LINES);
    for (int i = 0; i < 36; i++) {
        float angle = 2.0f * PI * i / 36.0f;
        float cx = 800.0f, cy = sunY;
        float r_inner = 50.0f, r_outer = 70.0f;
        float x_inner = cx + r_inner * cosf(angle);
        float y_inner = cy + r_inner * sinf(angle);
        float x_outer = cx + r_outer * cosf(angle);
        float y_outer = cy + r_outer * sinf(angle);
        glVertex2f(x_inner, y_inner);
        glVertex2f(x_outer, y_outer);
    }
    glEnd();

    drawMountain(0,   185, 150, 400, 300, 185, 0.25f, 0.55f, 0.25f);
    drawMountain(220, 185, 430, 430, 640, 185, 0.20f, 0.50f, 0.20f);
    drawMountain(510, 185, 710, 395, 900, 185, 0.18f, 0.45f, 0.18f);


    glColor3f(0.30f, 0.60f, 0.18f);
    glBegin(GL_QUADS);
    glVertex2f(0,0); glVertex2f(W,0);
    glVertex2f(W,185); glVertex2f(0,185);
    glEnd();



    drawCloud(200, 500);
    drawCloud(500, 540);

    drawHouse(80, 185, 180, 120, 0.92f, 0.74f, 0.52f);
    drawHouse(320, 185, 220, 130, 0.95f, 0.95f, 0.70f);

    drawTree(650, 185, 30, 120);

    drawRoad(60, 70);

    drawBird(200 + birdOffset, 500, 15);
    drawBird(250 + birdOffset, 520, 20);
    drawBird(300 + birdOffset, 480, 18);


    drawFence(60, 185, 250, 60, 8);
    drawFence(320, 185, 220, 60, 7);

    glFlush();
}


void init()
{
    glClearColor(0.53f,0.81f,0.98f,1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,W,0,H);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Village Scenery");
    init();
    glutTimerFunc(0, update, 0);
    glutTimerFunc(0, updateSun, 0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
