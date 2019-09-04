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
struct TYPE_7__ {int s; int t; } ;
typedef  int GLdouble ;
typedef  TYPE_1__ GLUvertex ;

/* Variables and functions */
 scalar_t__ VertLeq (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

GLdouble __gl_edgeEval( GLUvertex *u, GLUvertex *v, GLUvertex *w )
{
  /* Given three vertices u,v,w such that VertLeq(u,v) && VertLeq(v,w),
   * evaluates the t-coord of the edge uw at the s-coord of the vertex v.
   * Returns v->t - (uw)(v->s), ie. the signed distance from uw to v.
   * If uw is vertical (and thus passes thru v), the result is zero.
   *
   * The calculation is extremely accurate and stable, even when v
   * is very close to u or w.  In particular if we set v->t = 0 and
   * let r be the negated result (this evaluates (uw)(v->s)), then
   * r is guaranteed to satisfy MIN(u->t,w->t) <= r <= MAX(u->t,w->t).
   */
  GLdouble gapL, gapR;

  assert( VertLeq( u, v ) && VertLeq( v, w ));
  
  gapL = v->s - u->s;
  gapR = w->s - v->s;

  if( gapL + gapR > 0 ) {
    if( gapL < gapR ) {
      return (v->t - u->t) + (u->t - w->t) * (gapL / (gapL + gapR));
    } else {
      return (v->t - w->t) + (w->t - u->t) * (gapR / (gapL + gapR));
    }
  }
  /* vertical line */
  return 0;
}