#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


/*void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);

    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.5f, 0.4f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Line Example");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}*/

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f); //Black
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.33f);
        glVertex2f( 1.0f, 0.33f);
        glVertex2f( 1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); //Red
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.33f);
        glVertex2f( 1.0f, -0.33f);
        glVertex2f( 1.0f, 0.33f);
        glVertex2f(-1.0f, 0.33f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); //Yellow
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, -0.33f);
        glVertex2f(-1.0f, -0.33f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Germany Flag");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
