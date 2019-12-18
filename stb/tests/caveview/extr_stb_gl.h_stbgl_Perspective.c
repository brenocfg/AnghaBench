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
 int /*<<< orphan*/  GL_VIEWPORT ; 
 scalar_t__ atan (float) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gluPerspective (float,float,float,float) ; 
 int /*<<< orphan*/  stbgl_deg2rad (float) ; 
 scalar_t__ stbgl_rad2deg (float) ; 
 scalar_t__ tan (int /*<<< orphan*/ ) ; 

void stbgl_Perspective(float zoom, float max_hfov, float max_vfov, float znear, float zfar)
{
   float unit_width, unit_height, aspect, vfov;
   int data[4],w,h;
   glGetIntegerv(GL_VIEWPORT, data);
   w = data[2];
   h = data[3];
   aspect = (float) w / h;

   if (max_hfov <= 0) max_hfov = 179;
   if (max_vfov <= 0) max_vfov = 179;

   // convert max_hfov, max_vfov to worldspace width at depth=1
   unit_width  = (float) tan(stbgl_deg2rad(max_hfov/2)) * 2;
   unit_height = (float) tan(stbgl_deg2rad(max_vfov/2)) * 2;
   // check if hfov = max_hfov is enough to satisfy it
   if (unit_width <= aspect * unit_height) {
      float height = unit_width / aspect;
      vfov = (float) atan((     height/2) / zoom);
   } else {
      vfov = (float) atan((unit_height/2) / zoom);
   }
   vfov = (float) stbgl_rad2deg(vfov * 2);
   gluPerspective(vfov, aspect, znear, zfar);
}