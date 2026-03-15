#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>

const int W = 900, H = 600;

void DDA(int x1, int y1, int x2, int y2, float r, float g, float b)
{
    float dx    = (float)(x2 - x1);
    float dy    = (float)(y2 - y1);
    float steps = (fabsf(dx) > fabsf(dy)) ? fabsf(dx) : fabsf(dy);
    if (steps == 0.0f)
    {
        glColor3f(r, g, b);
        glBegin(GL_POINTS);
        glVertex2i(x1, y1);
        glEnd();
        return;
    }
    float xi = dx / steps, yi = dy / steps;
    float x = (float)x1,   y  = (float)y1;
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    for (int i = 0; i <= (int)steps; i++)
    {
        glVertex2i((int)roundf(x), (int)roundf(y));
        x += xi; y += yi;
    }
    glEnd();
}

void Bresenham(int x1, int y1, int x2, int y2, float r, float g, float b)
{
    int dx = abs(x2-x1), dy = abs(y2-y1);
    int sx = (x1<x2)?1:-1, sy = (y1<y2)?1:-1;
    int err = dx - dy;
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    while (true)
    {
        glVertex2i(x1, y1);
        if (x1==x2 && y1==y2) break;
        int e2 = 2*err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
    glEnd();
}

void MidpointCircle(int cx, int cy, int radius, float r, float g, float b)
{
    int x = 0, y = radius, p = 1 - radius;
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    auto plot8 = [&]()
    {
        glVertex2i(cx+x,cy+y); glVertex2i(cx-x,cy+y);
        glVertex2i(cx+x,cy-y); glVertex2i(cx-x,cy-y);
        glVertex2i(cx+y,cy+x); glVertex2i(cx-y,cy+x);
        glVertex2i(cx+y,cy-x); glVertex2i(cx-y,cy-x);
    };
    plot8();
    while (x < y)
    {
        x++;
        if (p < 0) p += 2*x+1;
        else { y--; p += 2*(x-y)+1; }
        plot8();
    }
    glEnd();
}

void FilledCircle(int cx, int cy, int radius, float r, float g, float b)
{
    int x = 0, y = radius, p = 1 - radius;
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    auto hSpan = [&](int yy, int hw)
    {
        for (int i = cx-hw; i <= cx+hw; i++) glVertex2i(i, yy);
    };
    hSpan(cy+y,x); hSpan(cy-y,x); hSpan(cy+x,y); hSpan(cy-x,y);
    while (x < y)
    {
        x++;
        if (p < 0) p += 2*x+1;
        else { y--; p += 2*(x-y)+1; }
        hSpan(cy+y,x); hSpan(cy-y,x); hSpan(cy+x,y); hSpan(cy-x,y);
    }
    glEnd();
}

void fillRect(int x1, int y1, int x2, int y2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
            glVertex2i(x, y);
    glEnd();
}

void MidpointArch(int cx, int cy, int radius, float r, float g, float b, int thickness, int ymin)
{
    for (int t = 0; t < thickness; t++)
    {
        int x = 0, y = radius - t, p = 1 - (radius - t);
        glColor3f(r, g, b);
        glBegin(GL_POINTS);
        while (x <= y) {
            int px1 = cx + x, py1 = cy + y;
            int px2 = cx - x, py2 = cy + y;
            int px3 = cx + y, py3 = cy + x;
            int px4 = cx - y, py4 = cy + x;

            if (py1 >= ymin) glVertex2i(px1, py1);
            if (py2 >= ymin) glVertex2i(px2, py2);
            if (py3 >= ymin) glVertex2i(px3, py3);
            if (py4 >= ymin) glVertex2i(px4, py4);

            if (p < 0) p += 2*x + 3;
            else { p += 2*(x - y) + 5; y--; }
            x++;
        }
        glEnd();
    }
}

void Flower(int cx, int cy, int radius, float r, float g, float b)
{
    FilledCircle(cx, cy, radius, r, g, b);
    DDA(cx, cy - radius, cx, cy - radius - 40, 0.0f, 0.5f, 0.0f);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.5f);

    //Ground
    fillRect(0, 0, W, 115, 0.18f, 0.38f, 0.10f);

    //Sun
    const int SCX = 790, SCY = 530;
    const int SR  = 30;
    FilledCircle(SCX, SCY, SR, 1.00f, 0.87f, 0.05f);
    for (int deg = 0; deg < 360; deg += 30)
    {
        float rad  = deg * 3.14159265f / 180.0f;
        float cosA = cosf(rad), sinA = sinf(rad);
        int rx1 = SCX + (int)roundf((SR + 6)  * cosA);
        int ry1 = SCY + (int)roundf((SR + 6)  * sinA);
        int rx2 = SCX + (int)roundf((SR + 26) * cosA);
        int ry2 = SCY + (int)roundf((SR + 26) * sinA);
        DDA(rx1, ry1, rx2, ry2, 1.00f, 0.87f, 0.05f);
    }

    //Flagpole
    for (int px = 78; px <= 80; px++)
        DDA(px, 115, px, 425, 0.42f, 0.26f, 0.07f);

    //Flag rectangle
    int left   = 81, right  = 241;
    int bottom = 320, top   = 420;
    Bresenham(left,  bottom, right, bottom, 0.0f, 0.29f, 0.21f);
    Bresenham(right, bottom, right, top,    0.0f, 0.29f, 0.21f);
    Bresenham(right, top,    left,  top,    0.0f, 0.29f, 0.21f);
    Bresenham(left,  top,    left,  bottom, 0.0f, 0.29f, 0.21f);
    fillRect(left+1, bottom+1, right-1, top-1, 0.0f, 0.416f, 0.306f);
    int flagCenterX = (left + right) / 2;
    int flagCenterY = (bottom + top) / 2;

    FilledCircle(flagCenterX - 15, flagCenterY, 35, 0.957f, 0.165f, 0.255f);

    //Base platform
    fillRect(390, 115, 755, 158, 0.0f, 0.0f, 0.0f);
    fillRect(420, 104, 725, 115, 0.0f, 0.0f, 0.0f);

    //Pillers
    struct { int xl, xr, top; } pils[] =
    {
        {390, 420, 320},
        {470, 500, 360},
        {540, 595, 400},
        {640, 670, 360},
        {720, 750, 320}
    };

    const int BASE = 158;

    for (auto& p : pils)
    {
        fillRect(p.xl, BASE, p.xr, p.top, 1.0f, 1.0f, 1.0f);
        Bresenham(p.xl, BASE, p.xl, p.top, 0.7f, 0.7f, 0.7f);
        Bresenham(p.xr, BASE, p.xr, p.top, 0.7f, 0.7f, 0.7f);
        Bresenham(p.xl, p.top, p.xr, p.top, 0.7f, 0.7f, 0.7f);
    }

    //Top arch
    MidpointArch(570, 200, 220, 0.6f, 0.6f, 0.6f, 4, 320);

    for (auto& p : pils) {
        fillRect(p.xl, BASE, p.xr, p.top, 1.0f, 1.0f, 1.0f);
        Bresenham(p.xl, BASE, p.xl, p.top, 0.7f, 0.7f, 0.7f);
        Bresenham(p.xr, BASE, p.xr, p.top, 0.7f, 0.7f, 0.7f);
        Bresenham(p.xl, p.top, p.xr, p.top, 0.7f, 0.7f, 0.7f);
        int mx = (p.xl + p.xr) / 2;
        DDA(mx, BASE+5, mx, p.top-8, 0.5f, 0.5f, 0.5f);
    }

    //Red circle
    FilledCircle(570, 250, 60, 0.95f, 0.0f, 0.0f);

    //Flowers
    Flower(150, 140, 8, 1.0f, 0.0f, 0.0f);
    Flower(190, 152, 9, 1.0f, 0.5f, 0.0f);
    Flower(240, 135, 7, 1.0f, 1.0f, 0.0f);
    Flower(280, 148, 8, 1.0f, 0.0f, 0.0f);
    Flower(330, 142, 9, 1.0f, 0.5f, 0.0f);
    Flower(370, 137, 7, 1.0f, 1.0f, 0.0f);
    Flower(420, 150, 8, 1.0f, 0.0f, 0.0f);
    Flower(470, 138, 9, 1.0f, 0.5f, 0.0f);
    Flower(520, 145, 7, 1.0f, 1.0f, 0.0f);
    Flower(580, 140, 8, 1.0f, 0.0f, 0.0f);

    glFlush();
}

void init()
{
    glClearColor(0.48f, 0.78f, 0.96f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bangladesh Tribute Scene");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
