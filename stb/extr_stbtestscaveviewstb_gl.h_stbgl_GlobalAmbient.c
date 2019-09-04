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
 int /*<<< orphan*/  GL_LIGHT_MODEL_AMBIENT ; 
 int /*<<< orphan*/  glLightModelfv (int /*<<< orphan*/ ,float*) ; 

void stbgl_GlobalAmbient(float r, float g, float b)
{
   float v[4] = { r,g,b,0 };
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, v);
}