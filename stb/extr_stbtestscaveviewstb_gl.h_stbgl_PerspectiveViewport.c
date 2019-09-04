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
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glScissor (int,int,int,int) ; 
 int /*<<< orphan*/  glViewport (int,int,int,int) ; 
 int /*<<< orphan*/  stbgl_Perspective (float,float,float,float,float) ; 

void stbgl_PerspectiveViewport(int x, int y, int w, int h, float zoom, float min_hfov, float min_vfov, float znear, float zfar)
{
   if (znear <= 0.0001f) znear = 0.0001f;
   glViewport(x,y,w,h);
   glScissor(x,y,w,h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   stbgl_Perspective(zoom, min_hfov, min_vfov, znear, zfar);
   glMatrixMode(GL_MODELVIEW);
}