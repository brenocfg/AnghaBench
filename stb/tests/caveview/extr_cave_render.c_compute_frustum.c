#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float x; } ;
typedef  scalar_t__ GLdouble ;

/* Variables and functions */
 int /*<<< orphan*/  GL_MODELVIEW_MATRIX ; 
 int /*<<< orphan*/  GL_PROJECTION_MATRIX ; 
 TYPE_1__* frustum ; 
 int /*<<< orphan*/  glGetDoublev (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  matd_mul (scalar_t__**,scalar_t__**,scalar_t__**) ; 

__attribute__((used)) static void compute_frustum(void)
{
   int i;
   GLdouble mv[4][4],proj[4][4], mvproj[4][4];
   glGetDoublev(GL_MODELVIEW_MATRIX , mv[0]);
   glGetDoublev(GL_PROJECTION_MATRIX, proj[0]);
   matd_mul(mvproj, proj, mv);
   for (i=0; i < 4; ++i) {
      (&frustum[0].x)[i] = (float) (mvproj[3][i] + mvproj[0][i]);
      (&frustum[1].x)[i] = (float) (mvproj[3][i] - mvproj[0][i]);
      (&frustum[2].x)[i] = (float) (mvproj[3][i] + mvproj[1][i]);
      (&frustum[3].x)[i] = (float) (mvproj[3][i] - mvproj[1][i]);
      (&frustum[4].x)[i] = (float) (mvproj[3][i] + mvproj[2][i]);
      (&frustum[5].x)[i] = (float) (mvproj[3][i] - mvproj[2][i]);
   }   
}