#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ t; scalar_t__ s; } ;
typedef  scalar_t__ GLdouble ;
typedef  TYPE_1__ GLUvertex ;

/* Variables and functions */
 scalar_t__ TransLeq (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

GLdouble __gl_transSign( GLUvertex *u, GLUvertex *v, GLUvertex *w )
{
  /* Returns a number whose sign matches TransEval(u,v,w) but which
   * is cheaper to evaluate.  Returns > 0, == 0 , or < 0
   * as v is above, on, or below the edge uw.
   */
  GLdouble gapL, gapR;

  assert( TransLeq( u, v ) && TransLeq( v, w ));
  
  gapL = v->t - u->t;
  gapR = w->t - v->t;

  if( gapL + gapR > 0 ) {
    return (v->s - w->s) * gapL + (v->s - u->s) * gapR;
  }
  /* vertical line */
  return 0;
}