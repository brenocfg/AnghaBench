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
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_AMBIENT ; 
 int /*<<< orphan*/  GL_AMBIENT_AND_DIFFUSE ; 
 scalar_t__ GL_COLOR_MATERIAL ; 
 int /*<<< orphan*/  GL_DIFFUSE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 scalar_t__ GL_LIGHT0 ; 
 int /*<<< orphan*/  GL_POSITION ; 
 int /*<<< orphan*/  GL_SPECULAR ; 
 int /*<<< orphan*/  glColorMaterial (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (scalar_t__) ; 
 int /*<<< orphan*/  glLightfv (scalar_t__,int /*<<< orphan*/ ,float*) ; 
 float sqrt (float) ; 

void stbgl_SimpleLight(int index, float bright, float x, float y, float z)
{
   float d = (float) (1.0f/sqrt(x*x+y*y+z*z));
   float dir[4] = { x*d,y*d,z*d,0 }, zero[4] = { 0,0,0,0 };
   float c[4] = { bright,bright,bright,0 };
   GLuint light = GL_LIGHT0 + index;
   glLightfv(light, GL_POSITION, dir);
   glLightfv(light, GL_DIFFUSE, c);
   glLightfv(light, GL_AMBIENT, zero);
   glLightfv(light, GL_SPECULAR, zero);
   glEnable(light);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
}