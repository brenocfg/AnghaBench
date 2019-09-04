#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* eUp; } ;
struct TYPE_13__ {TYPE_1__* eUp; scalar_t__ fixUpperEdge; } ;
struct TYPE_12__ {int /*<<< orphan*/  Sym; } ;
struct TYPE_11__ {int /*<<< orphan*/  Lnext; int /*<<< orphan*/ * Org; } ;
typedef  int /*<<< orphan*/  GLUvertex ;
typedef  int /*<<< orphan*/  GLUhalfEdge ;
typedef  TYPE_3__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  FixUpperEdge (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* RegionAbove (TYPE_3__*) ; 
 TYPE_6__* RegionBelow (TYPE_3__*) ; 
 int /*<<< orphan*/ * __gl_meshConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ActiveRegion *TopLeftRegion( ActiveRegion *reg )
{
  GLUvertex *org = reg->eUp->Org;
  GLUhalfEdge *e;

  /* Find the region above the uppermost edge with the same origin */
  do {
    reg = RegionAbove( reg );
  } while( reg->eUp->Org == org );

  /* If the edge above was a temporary edge introduced by ConnectRightVertex,
   * now is the time to fix it.
   */
  if( reg->fixUpperEdge ) {
    e = __gl_meshConnect( RegionBelow(reg)->eUp->Sym, reg->eUp->Lnext );
    if (e == NULL) return NULL;
    if ( !FixUpperEdge( reg, e ) ) return NULL;
    reg = RegionAbove( reg );
  }
  return reg;
}