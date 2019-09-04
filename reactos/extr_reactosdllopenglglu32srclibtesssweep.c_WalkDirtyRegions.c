#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ fixUpperEdge; TYPE_2__* eUp; scalar_t__ dirty; } ;
struct TYPE_22__ {scalar_t__ Dst; scalar_t__ Org; } ;
struct TYPE_21__ {scalar_t__ event; int /*<<< orphan*/  env; } ;
typedef  TYPE_1__ GLUtesselator ;
typedef  TYPE_2__ GLUhalfEdge ;
typedef  TYPE_3__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  AddWinding (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ CheckForIntersect (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ CheckForLeftSplice (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  CheckForRightSplice (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteRegion (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ FALSE ; 
 TYPE_3__* RegionAbove (TYPE_3__*) ; 
 TYPE_3__* RegionBelow (TYPE_3__*) ; 
 int /*<<< orphan*/  __gl_meshDelete (TYPE_2__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void WalkDirtyRegions( GLUtesselator *tess, ActiveRegion *regUp )
/*
 * When the upper or lower edge of any region changes, the region is
 * marked "dirty".  This routine walks through all the dirty regions
 * and makes sure that the dictionary invariants are satisfied
 * (see the comments at the beginning of this file).  Of course
 * new dirty regions can be created as we make changes to restore
 * the invariants.
 */
{
  ActiveRegion *regLo = RegionBelow(regUp);
  GLUhalfEdge *eUp, *eLo;

  for( ;; ) {
    /* Find the lowest dirty region (we walk from the bottom up). */
    while( regLo->dirty ) {
      regUp = regLo;
      regLo = RegionBelow(regLo);
    }
    if( ! regUp->dirty ) {
      regLo = regUp;
      regUp = RegionAbove( regUp );
      if( regUp == NULL || ! regUp->dirty ) {
	/* We've walked all the dirty regions */
	return;
      }
    }
    regUp->dirty = FALSE;
    eUp = regUp->eUp;
    eLo = regLo->eUp;

    if( eUp->Dst != eLo->Dst ) {
      /* Check that the edge ordering is obeyed at the Dst vertices. */
      if( CheckForLeftSplice( tess, regUp )) {

	/* If the upper or lower edge was marked fixUpperEdge, then
	 * we no longer need it (since these edges are needed only for
	 * vertices which otherwise have no right-going edges).
	 */
	if( regLo->fixUpperEdge ) {
	  DeleteRegion( tess, regLo );
	  if ( !__gl_meshDelete( eLo ) ) longjmp(tess->env,1);
	  regLo = RegionBelow( regUp );
	  eLo = regLo->eUp;
	} else if( regUp->fixUpperEdge ) {
	  DeleteRegion( tess, regUp );
	  if ( !__gl_meshDelete( eUp ) ) longjmp(tess->env,1);
	  regUp = RegionAbove( regLo );
	  eUp = regUp->eUp;
	}
      }
    }
    if( eUp->Org != eLo->Org ) {
      if(    eUp->Dst != eLo->Dst
	  && ! regUp->fixUpperEdge && ! regLo->fixUpperEdge
	  && (eUp->Dst == tess->event || eLo->Dst == tess->event) )
      {
	/* When all else fails in CheckForIntersect(), it uses tess->event
	 * as the intersection location.  To make this possible, it requires
	 * that tess->event lie between the upper and lower edges, and also
	 * that neither of these is marked fixUpperEdge (since in the worst
	 * case it might splice one of these edges into tess->event, and
	 * violate the invariant that fixable edges are the only right-going
	 * edge from their associated vertex).
	 */
	if( CheckForIntersect( tess, regUp )) {
	  /* WalkDirtyRegions() was called recursively; we're done */
	  return;
	}
      } else {
	/* Even though we can't use CheckForIntersect(), the Org vertices
	 * may violate the dictionary edge ordering.  Check and correct this.
	 */
	(void) CheckForRightSplice( tess, regUp );
      }
    }
    if( eUp->Org == eLo->Org && eUp->Dst == eLo->Dst ) {
      /* A degenerate loop consisting of only two edges -- delete it. */
      AddWinding( eLo, eUp );
      DeleteRegion( tess, regUp );
      if ( !__gl_meshDelete( eUp ) ) longjmp(tess->env,1);
      regUp = RegionAbove( regLo );
    }
  }
}