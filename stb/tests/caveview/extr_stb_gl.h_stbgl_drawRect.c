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
 int /*<<< orphan*/  GL_POLYGON ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glTexCoord2f (int,int) ; 
 int /*<<< orphan*/  glVertex2f (float,float) ; 

void stbgl_drawRect(float x0, float y0, float x1, float y1)
{
   glBegin(GL_POLYGON);
      glTexCoord2f(0,0); glVertex2f(x0,y0);
      glTexCoord2f(1,0); glVertex2f(x1,y0);
      glTexCoord2f(1,1); glVertex2f(x1,y1);
      glTexCoord2f(0,1); glVertex2f(x0,y1);
   glEnd();
}