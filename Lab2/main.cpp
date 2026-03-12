#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

// Function to draw a circle using parametric equations
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON); // Filled circle
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //House base
    glColor3f(0.6f, 0.0f, 0.8f); //Violet
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.6f);
        glVertex2f(-0.2f, -0.6f);
        glVertex2f(-0.2f, -0.3f);
        glVertex2f(-0.8f, -0.3f);
    glEnd();

    //Roof
    glColor3f(0.5f, 0.5f, 0.5f); //Grey
        glBegin(GL_QUADS);
        glVertex2f(-0.85f, -0.3f);
        glVertex2f(-0.15f, -0.3f);
        glVertex2f(-0.25f, -0.1f);
        glVertex2f(-0.75f, -0.1f);

    //Door
    glColor3f(0.7f, 0.9f, 1.0f); //Light blue
    glBegin(GL_QUADS);
        glVertex2f(-0.55f, -0.6f);
        glVertex2f(-0.45f, -0.6f);
        glVertex2f(-0.45f, -0.45f);
        glVertex2f(-0.55f, -0.45f);
    glEnd();

    //Left window
    glColor3f(0.7f, 0.9f, 1.0f); //Light blue
    glBegin(GL_QUADS);
        glVertex2f(-0.75f, -0.5f);
        glVertex2f(-0.65f, -0.5f);
        glVertex2f(-0.65f, -0.4f);
        glVertex2f(-0.75f, -0.4f);
    glEnd();

    //Right window
    glColor3f(0.7f, 0.9f, 1.0f); //Light blue
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, -0.5f);
        glVertex2f(-0.25f, -0.5f);
        glVertex2f(-0.25f, -0.4f);
        glVertex2f(-0.35f, -0.4f);
    glEnd();

    //Sun
    glColor3f(1.0f, 0.84f, 0.0f); //Golden
    drawCircle(0.0f, 0.5f, 0.15f, 100);

    //Rays
    glColor3f(1.0f, 0.84f, 0.0f); //Golden
    glBegin(GL_LINES);
    for (int i = 0; i < 18; i++)
    {
        float angle = 2.0f * 3.1415926f * i / 18.0f;
        float x_inner = 0.0f + 0.15f * cosf(angle);
        float y_inner = 0.5f + 0.15f * sinf(angle);
        float x_outer = 0.0f + 0.25f * cosf(angle);
        float y_outer = 0.5f + 0.25f * sinf(angle);
        glVertex2f(x_inner, y_inner);
        glVertex2f(x_outer, y_outer);
    }
    glEnd();


    //Pole
    glColor3f(0.0f, 0.0f, 0.0f); //Black
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glVertex2f(0.4f, -0.6f);
        glVertex2f(0.4f, 0.4f);
    glEnd();
    glLineWidth(1.0f);


    //Rectangle
    glColor3f(0.0f, 0.6f, 0.0f); //Green
    glBegin(GL_QUADS);
        glVertex2f(0.4f, 0.4f);
        glVertex2f(0.8f, 0.4f);
        glVertex2f(0.8f, 0.2f);
        glVertex2f(0.4f, 0.2f);
    glEnd();

    //Circle
    glColor3f(1.0f, 0.0f, 0.0f); //Red
    drawCircle(0.6f, 0.3f, 0.08f, 100);


    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("House, Sun, and Flag");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //White
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
