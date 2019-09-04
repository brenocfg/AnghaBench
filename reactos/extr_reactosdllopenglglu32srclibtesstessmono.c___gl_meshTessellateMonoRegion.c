#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* anEdge; } ;
struct TYPE_9__ {struct TYPE_9__* Sym; struct TYPE_9__* Lnext; struct TYPE_9__* Lprev; int /*<<< orphan*/  Org; int /*<<< orphan*/  Dst; } ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  TYPE_2__ GLUface ;

/* Variables and functions */
 scalar_t__ EdgeGoesLeft (TYPE_1__*) ; 
 scalar_t__ EdgeGoesRight (TYPE_1__*) ; 
 scalar_t__ EdgeSign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VertLeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* __gl_meshConnect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

int __gl_meshTessellateMonoRegion( GLUface *face )
{
  GLUhalfEdge *up, *lo;

  /* All edges are oriented CCW around the boundary of the region.
   * First, find the half-edge whose origin vertex is rightmost.
   * Since the sweep goes from left to right, face->anEdge should
   * be close to the edge we want.
   */
  up = face->anEdge;
  assert( up->Lnext != up && up->Lnext->Lnext != up );

  for( ; VertLeq( up->Dst, up->Org ); up = up->Lprev )
    ;
  for( ; VertLeq( up->Org, up->Dst ); up = up->Lnext )
    ;
  lo = up->Lprev;

  while( up->Lnext != lo ) {
    if( VertLeq( up->Dst, lo->Org )) {
      /* up->Dst is on the left.  It is safe to form triangles from lo->Org.
       * The EdgeGoesLeft test guarantees progress even when some triangles
       * are CW, given that the upper and lower chains are truly monotone.
       */
      while( lo->Lnext != up && (EdgeGoesLeft( lo->Lnext )
	     || EdgeSign( lo->Org, lo->Dst, lo->Lnext->Dst ) <= 0 )) {
	GLUhalfEdge *tempHalfEdge= __gl_meshConnect( lo->Lnext, lo );
	if (tempHalfEdge == NULL) return 0;
	lo = tempHalfEdge->Sym;
      }
      lo = lo->Lprev;
    } else {
      /* lo->Org is on the left.  We can make CCW triangles from up->Dst. */
      while( lo->Lnext != up && (EdgeGoesRight( up->Lprev )
	     || EdgeSign( up->Dst, up->Org, up->Lprev->Org ) >= 0 )) {
	GLUhalfEdge *tempHalfEdge= __gl_meshConnect( up, up->Lprev );
	if (tempHalfEdge == NULL) return 0;
	up = tempHalfEdge->Sym;
      }
      up = up->Lnext;
    }
  }

  /* Now lo->Org == up->Dst == the leftmost vertex.  The remaining region
   * can be tessellated in a fan from this leftmost vertex.
   */
  assert( lo->Lnext != up );
  while( lo->Lnext->Lnext != up ) {
    GLUhalfEdge *tempHalfEdge= __gl_meshConnect( lo->Lnext, lo );
    if (tempHalfEdge == NULL) return 0;
    lo = tempHalfEdge->Sym;
  }

  return 1;
}