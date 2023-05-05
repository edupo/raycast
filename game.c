#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "player.h"
#include "map.h"
#include "vector.h"

#define WIDTH 1024
#define HEIGHT 512

Player* p;
Map* m;

int map[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    };

void drawRays2D(Player* p, Map* m){
    int r, mx, my, mp, dof; float rx, ry, ra, xo, yo;
    ra = p->angle;
    V2i mc = map_point_to_coord(m, p->position);
    for (r = 0; r < 1; r++)
    {
        // --- Check Horizontal Grid lines    
        dof = 0.0;
        float atan=1.0/tan(ra);
        float sin_a = sin(ra);

        if(sin_a>0.001){ 
            ry = mc.y * m->tile_size - 0.0001; 
            rx = p->position.x + (p->position.y - ry) * atan;
            yo = -m->tile_size;
            xo = -yo*atan;
        }
        else if(sin_a<-0.001){
            ry = mc.y * m->tile_size + 64.0;
            rx = p->position.x + (p->position.y - ry) * atan;
            yo = m->tile_size;
            xo = -yo*atan;
        }
        else { rx=p->position.x; ry=p->position.y, dof=8; }
        while(dof<8){
            mx = (int) (rx) >> 6; 
            my = (int) (ry) >> 6;
            mp = my * m->width + mx;
            if (mp < m->lenght && m->data[mp] == 1){ dof = 8; } // hit
            else { rx+=xo; ry+=yo; dof+= 1; } // next line
        }
        glColor3f(0,1,0);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(p->position.x, p->position.y);
        glVertex2i(rx, ry);
        glEnd();

        // --- Check Vertical Grid lines    
        dof = 0.0;
        float ntan = tan(ra);
        float cos_a = cos(ra);

        if(cos_a>0.001){ 
            rx = mc.x * m->tile_size + 64.0; 
            ry = p->position.y + (p->position.x - rx) * ntan;
            xo = m->tile_size;
            yo = -xo*ntan;
        }
        else if(cos_a<-0.001){
            rx = mc.x * m->tile_size - 0.0001;
            ry = p->position.y + (p->position.x - rx) * ntan;
            xo = -m->tile_size;
            yo = -xo*ntan;
        }
        else { rx=p->position.x; ry=p->position.y, dof=8; }
        while(dof<8){
            mx = (int) (rx) >> 6; 
            my = (int) (ry) >> 6;
            mp = my * m->width + mx;
            if (mp < m->lenght && m->data[mp] == 1){ dof = 8; } // hit
            else { rx+=xo; ry+=yo; dof+= 1; } // next line
        }
        glColor3f(1,0,0);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(p->position.x, p->position.y);
        glVertex2i(rx, ry);
        glEnd();
    }
    
}

void drawPlayer(Player* p)
{
    V2f b = v2f_add(p->position, v2f_mul(p->direction, 25));

    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(p->position.x, p->position.y);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(p->position.x, p->position.y);
    glVertex2i(b.x, b.y);
    glEnd();
}

void buttons(unsigned char key, int x, int y)
{
    if (key == 'a') player_set_angle(p, p->angle-=.1);
    if (key == 'd') player_set_angle(p, p->angle+=.1);
    if (key == 'w') player_move_forward(p);
    if (key == 's') player_move_backwards(p);
    glutPostRedisplay();
}

void drawMap2D(Map* m, int tile_size)
{
    int x, y, xo, yo;
    for (y = 0; y < m->height; y++)
    {
        for (x = 0; x < m->width; x++)
        {
            if (m->data[y * m->width + x] == 1) glColor3f(1, 1, 1); else glColor3f(0, 0, 0);
            xo = x*tile_size; yo=y*tile_size;
            glBegin(GL_QUADS);
            glVertex2i(xo+1,           yo+1);
            glVertex2i(xo+1,           yo+tile_size-1);
            glVertex2i(xo+tile_size-1, yo+tile_size-1);
            glVertex2i(xo+tile_size-1, yo+1);
            glEnd();
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap2D(m, 64);
    drawPlayer(p);
    drawRays2D(p, m);
    glutSwapBuffers();
}

void init()
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    player_init(p, 300.0, 300.0, 0.0, 5.0);
    m = map_create(8, 8, map);
}

int main(int argc, char **argv)
{
    Player _p;
    p = &_p;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Game");
    init();
    glutKeyboardFunc(buttons);
    glutDisplayFunc(display);
    glutMainLoop();
    map_free(m);
    return 0;
}