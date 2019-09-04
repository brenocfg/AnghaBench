#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  pqHandle; } ;
struct TYPE_24__ {int dirty; TYPE_2__* eUp; } ;
struct TYPE_23__ {struct TYPE_23__* Oprev; int /*<<< orphan*/  Sym; TYPE_6__* Org; int /*<<< orphan*/  Dst; } ;
struct TYPE_22__ {int /*<<< orphan*/  env; int /*<<< orphan*/  pq; } ;
struct TYPE_21__ {int dirty; } ;
typedef  TYPE_1__ GLUtesselator ;
typedef  TYPE_2__ GLUhalfEdge ;
typedef  TYPE_3__ ActiveRegion ;

/* Variables and functions */
 scalar_t__ EdgeSign (int /*<<< orphan*/ ,TYPE_6__*,TYPE_6__*) ; 
 int FALSE ; 
 TYPE_15__* RegionAbove (TYPE_3__*) ; 
 TYPE_3__* RegionBelow (TYPE_3__*) ; 
 int /*<<< orphan*/  SpliceMergeVertices (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  VertEq (TYPE_6__*,TYPE_6__*) ; 
 scalar_t__ VertLeq (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  __gl_meshSplice (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * __gl_meshSplitEdge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pqDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int CheckForRightSplice( GLUtesselator *tess, ActiveRegion *regUp )
/*
 * Check the upper and lower edge of "regUp", to make sure that the
 * eUp->Org is above eLo, or eLo->Org is below eUp (depending on which
 * origin is leftmost).
 *
 * The main purpose is to splice right-going edges with the same
 * dest vertex and nearly identical slopes (ie. we can't distinguish
 * the slopes numerically).  However the splicing can also help us
 * to recover from numerical errors.  For example, suppose at one
 * point we checked eUp and eLo, and decided that eUp->Org is barely
 * above eLo.  Then later, we split eLo into two edges (eg. from
 * a splice operation like this one).  This can change the result of
 * our test so that now eUp->Org is incident to eLo, or barely below it.
 * We must correct this condition to maintain the dictionary invariants.
 *
 * One possibility is to check these edges for intersection again
 * (ie. CheckForIntersect).  This is what we do if possible.  However
 * CheckForIntersect requires that tess->event lies between eUp and eLo,
 * so that it has something to fall back on when the intersection
 * calculation gives us an unusable answer.  So, for those cases where
 * we can't check for intersection, this routine fixes the problem
 * by just splicing the offending vertex into the other edge.
 * This is a guaranteed solution, no matter how degenerate things get.
 * Basically this is a combinatorial solution to a numerical problem.
 */
{
  ActiveRegion *regLo = RegionBelow(regUp);
  GLUhalfEdge *eUp = regUp->eUp;
  GLUhalfEdge *eLo = regLo->eUp;

  if( VertLeq( eUp->Org, eLo->Org )) {
    if( EdgeSign( eLo->Dst, eUp->Org, eLo->Org ) > 0 ) return FALSE;

    /* eUp->Org appears to be below eLo */
    if( ! VertEq( eUp->Org, eLo->Org )) {
      /* Splice eUp->Org into eLo */
      if ( __gl_meshSplitEdge( eLo->Sym ) == NULL) longjmp(tess->env,1);
      if ( !__gl_meshSplice( eUp, eLo->Oprev ) ) longjmp(tess->env,1);
      regUp->dirty = regLo->dirty = TRUE;

    } else if( eUp->Org != eLo->Org ) {
      /* merge the two vertices, discarding eUp->Org */
      pqDelete( tess->pq, eUp->Org->pqHandle ); /* __gl_pqSortDelete */
      SpliceMergeVertices( tess, eLo->Oprev, eUp );
    }
  } else {
    if( EdgeSign( eUp->Dst, eLo->Org, eUp->Org ) < 0 ) return FALSE;

    /* eLo->Org appears to be above eUp, so splice eLo->Org into eUp */
    RegionAbove(regUp)->dirty = regUp->dirty = TRUE;
    if (__gl_meshSplitEdge( eUp->Sym ) == NULL) longjmp(tess->env,1);
    if ( !__gl_meshSplice( eLo->Oprev, eUp ) ) longjmp(tess->env,1);
  }
  return TRUE;
}