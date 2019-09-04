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
typedef  int GLuint ;
typedef  double GLfloat ;

/* Variables and functions */

__attribute__((used)) static void
horner_bezier_curve(GLfloat *cp, GLfloat *out, GLfloat t,
                    GLuint dim, GLuint order)
{
  GLfloat s, powert;
  GLuint i, k, bincoeff;

  if(order >= 2)
  { 
    bincoeff = order-1;
    s = 1.0-t;

    for(k=0; k<dim; k++)
      out[k] = s*cp[k] + bincoeff*t*cp[dim+k];

    for(i=2, cp+=2*dim, powert=t*t; i<order; i++, powert*=t, cp +=dim)
    {
      bincoeff *= order-i;
      bincoeff /= i;

      for(k=0; k<dim; k++)
        out[k] = s*out[k] + bincoeff*powert*cp[k];
    }
  }
  else /* order=1 -> constant curve */
  { 
    for(k=0; k<dim; k++)
      out[k] = cp[k];
  } 
}