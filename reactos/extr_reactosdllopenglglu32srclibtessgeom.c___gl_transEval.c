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
struct TYPE_7__ {int t; int s; } ;
typedef  int GLdouble ;
typedef  TYPE_1__ GLUvertex ;

/* Variables and functions */
 scalar_t__ TransLeq (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

GLdouble __gl_transEval( GLUvertex *u, GLUvertex *v, GLUvertex *w )
{
  /* Given three vertices u,v,w such that TransLeq(u,v) && TransLeq(v,w),
   * evaluates the t-coord of the edge uw at the s-coord of the vertex v.
   * Returns v->s - (uw)(v->t), ie. the signed distance from uw to v.
   * If uw is vertical (and thus passes thru v), the result is zero.
   *
   * The calculation is extremely accurate and stable, even when v
   * is very close to u or w.  In particular if we set v->s = 0 and
   * let r be the negated result (this evaluates (uw)(v->t)), then
   * r is guaranteed to satisfy MIN(u->s,w->s) <= r <= MAX(u->s,w->s).
   */
  GLdouble gapL, gapR;

  assert( TransLeq( u, v ) && TransLeq( v, w ));
  
  gapL = v->t - u->t;
  gapR = w->t - v->t;

  if( gapL + gapR > 0 ) {
    if( gapL < gapR ) {
      return (v->s - u->s) + (u->s - w->s) * (gapL / (gapL + gapR));
    } else {
      return (v->s - w->s) + (w->s - u->s) * (gapR / (gapL + gapR));
    }
  }
  /* vertical line */
  return 0;
}