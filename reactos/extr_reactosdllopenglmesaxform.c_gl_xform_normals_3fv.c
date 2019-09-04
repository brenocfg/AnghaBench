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
typedef  size_t GLuint ;
typedef  int GLfloat ;
typedef  int GLdouble ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 int GL_SQRT (int) ; 

void gl_xform_normals_3fv( GLuint n, GLfloat v[][3], const GLfloat m[16],
                           GLfloat u[][3], GLboolean normalize )
{
   if (normalize) {
      /* Transform normals and scale to unit length */
      GLuint i;
      GLfloat m0 = m[0],  m4 = m[4],  m8 = m[8];
      GLfloat m1 = m[1],  m5 = m[5],  m9 = m[9];
      GLfloat m2 = m[2],  m6 = m[6],  m10 = m[10];
      for (i=0;i<n;i++) {
         GLdouble tx, ty, tz;
         {
            GLfloat ux = u[i][0],  uy = u[i][1],  uz = u[i][2];
            tx = ux * m0 + uy * m1 + uz * m2;
            ty = ux * m4 + uy * m5 + uz * m6;
            tz = ux * m8 + uy * m9 + uz * m10;
         }
         {
            GLdouble len, scale;
            len = GL_SQRT( tx*tx + ty*ty + tz*tz );
            scale = (len>1E-30) ? (1.0 / len) : 1.0;
            v[i][0] = tx * scale;
            v[i][1] = ty * scale;
            v[i][2] = tz * scale;
         }
      }
   }
   else {
      /* Just transform normals, don't scale */
      GLuint i;
      GLfloat m0 = m[0],  m4 = m[4],  m8 = m[8];
      GLfloat m1 = m[1],  m5 = m[5],  m9 = m[9];
      GLfloat m2 = m[2],  m6 = m[6],  m10 = m[10];
      for (i=0;i<n;i++) {
         GLfloat ux = u[i][0],  uy = u[i][1],  uz = u[i][2];
         v[i][0] = ux * m0 + uy * m1 + uz * m2;
         v[i][1] = ux * m4 + uy * m5 + uz * m6;
         v[i][2] = ux * m8 + uy * m9 + uz * m10;
      }
   }
}