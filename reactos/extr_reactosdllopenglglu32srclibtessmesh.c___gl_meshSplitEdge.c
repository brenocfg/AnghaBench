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
struct TYPE_10__ {int /*<<< orphan*/  winding; struct TYPE_10__* Sym; int /*<<< orphan*/  Rface; TYPE_1__* Dst; TYPE_1__* Org; struct TYPE_10__* Oprev; } ;
struct TYPE_9__ {TYPE_2__* anEdge; } ;
typedef  TYPE_2__ GLUhalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  Splice (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* __gl_meshAddEdgeVertex (TYPE_2__*) ; 

GLUhalfEdge *__gl_meshSplitEdge( GLUhalfEdge *eOrg )
{
  GLUhalfEdge *eNew;
  GLUhalfEdge *tempHalfEdge= __gl_meshAddEdgeVertex( eOrg );
  if (tempHalfEdge == NULL) return NULL;

  eNew = tempHalfEdge->Sym;

  /* Disconnect eOrg from eOrg->Dst and connect it to eNew->Org */
  Splice( eOrg->Sym, eOrg->Sym->Oprev );
  Splice( eOrg->Sym, eNew );

  /* Set the vertex and face information */
  eOrg->Dst = eNew->Org;
  eNew->Dst->anEdge = eNew->Sym;	/* may have pointed to eOrg->Sym */
  eNew->Rface = eOrg->Rface;
  eNew->winding = eOrg->winding;	/* copy old winding information */
  eNew->Sym->winding = eOrg->Sym->winding;

  return eNew;
}