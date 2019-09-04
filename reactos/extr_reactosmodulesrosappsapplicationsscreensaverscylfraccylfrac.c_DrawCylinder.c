#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int bval ; 
 int /*<<< orphan*/  cylinder ; 
 int /*<<< orphan*/  cylquality ; 
 int /*<<< orphan*/  glColor3f (int,int,int) ; 
 int /*<<< orphan*/  glPopMatrix () ; 
 int /*<<< orphan*/  glPushMatrix () ; 
 int /*<<< orphan*/  glRotatef (double,double,double,double) ; 
 int /*<<< orphan*/  glTranslatef (double,int,double) ; 
 int /*<<< orphan*/  gluCylinder (int /*<<< orphan*/ ,float,float,int,int /*<<< orphan*/ ,int) ; 
 int gval ; 
 float rotfactor ; 
 int rval ; 
 float wfactor ; 

void DrawCylinder(int n, float rota, float width)
{
    glPushMatrix();
    glColor3f(rval/n, gval/n, bval/n);
    glRotatef(rota, 0.0, 1.0, 0.0);
    gluCylinder(cylinder, width, width * wfactor, n * 0.5, cylquality, 1);
    glTranslatef(0.0, 0.0, -n * 0.5);
    gluCylinder(cylinder, width * wfactor, width, n * 0.5, cylquality, 1);
    if(n > 1)
    {
        float r = rota * rotfactor;
        glRotatef(90.0, 1.0, 0.0, 0.0);
        DrawCylinder(n - 1,  r, width * wfactor);
        glTranslatef(0.0, n, 0.0);
        DrawCylinder(n - 1, -r, width * wfactor);
    }
    glPopMatrix();
}