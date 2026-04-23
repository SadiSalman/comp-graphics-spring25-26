#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>


const int W = 800, H = 600;
int mode = 0;

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

void drawHouse()
{
    glColor3f(0.9f, 0.7f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, -0.3f);
        glVertex2f( 0.3f, -0.3f);
        glVertex2f( 0.3f,  0.3f);
        glVertex2f(-0.3f,  0.3f);
    glEnd();

    glColor3f(0.72f, 0.18f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.3f);
        glVertex2f( 0.35f, -0.3f);
        glVertex2f( 0.35f, -0.35f);
        glVertex2f(-0.35f, -0.35f);
    glEnd();

    // Roof
    glColor3f(0.72f, 0.18f, 0.12f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, 0.3f);
        glVertex2f( 0.35f, 0.3f);
        glVertex2f( 0.0f,  0.6f);
    glEnd();

    glColor3f(0.48f, 0.28f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, -0.3f);
        glVertex2f(0.20f, -0.3f);
        glVertex2f(0.20f,  0.15f);
        glVertex2f(0.05f,  0.15f);
    glEnd();
    glColor3f(1.0f, 0.85f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(0.17f, -0.10f);
    glEnd();
    glPointSize(1.5f);

    drawWindow(-0.25f, -0.05f, -0.05f, 0.15f);
}


void drawAxes() {
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2f(-1,0); glVertex2f(1,0);
        glVertex2f(0,-1); glVertex2f(0,1);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    if (mode == 0) {
        glPushMatrix();
        drawHouse();
        glPopMatrix();
    }

    glPushMatrix();
    switch(mode) {
        case 1:
            glTranslatef(0.4f, 0.3f, 0.0f);
            break;
        case 2:
            glRotatef(45, 0,0,1);
            break;
        case 3:
            glTranslatef(0.2f,0.2f,0);
            glRotatef(45,0,0,1);
            glTranslatef(-0.2f,-0.2f,0);
            break;
        case 4:
            glScalef(1.5f,0.5f,1.0f);
            break;
        case 5:
            glScalef(-1.0f,-1.0f,1.0f);
            break;
        case 6:
            glTranslatef(0.4f,0.3f,0);
            glRotatef(45,0,0,1);
            glScalef(1.5f,0.5f,1.0f);
            break;
        case 7:
            glRotatef(45,0,0,1);
            glTranslatef(0.4f,0.3f,0);
            glScalef(1.5f,0.5f,1.0f);
            break;
    }
    if (mode != 0) drawHouse();
    glPopMatrix();

    glFlush();
}

void keyboard(unsigned char key,int x,int y){
    switch(key){
        case '0': mode=0; break;
        case '1': mode=1; break;
        case '2': mode=2; break;
        case '3': mode=3; break;
        case '4': mode=4; break;
        case '5': mode=5; break;
        case '6': mode=6; break;
        case '7': mode=7; break;
    }
    glutPostRedisplay();
}

void init(){
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(W,H);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
