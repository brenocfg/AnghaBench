#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* anEdge; } ;
struct TYPE_13__ {TYPE_8__* Lface; int /*<<< orphan*/  Org; int /*<<< orphan*/  Dst; struct TYPE_13__* Lnext; struct TYPE_13__* Sym; } ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  int /*<<< orphan*/  GLUface ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KillFace (TYPE_8__*,TYPE_8__*) ; 
 TYPE_1__* MakeEdge (TYPE_1__*) ; 
 int /*<<< orphan*/  MakeFace (int /*<<< orphan*/ *,TYPE_1__*,TYPE_8__*) ; 
 int /*<<< orphan*/  Splice (TYPE_1__*,TYPE_1__*) ; 
 int TRUE ; 
 int /*<<< orphan*/ * allocFace () ; 

GLUhalfEdge *__gl_meshConnect( GLUhalfEdge *eOrg, GLUhalfEdge *eDst )
{
  GLUhalfEdge *eNewSym;
  int joiningLoops = FALSE;  
  GLUhalfEdge *eNew = MakeEdge( eOrg );
  if (eNew == NULL) return NULL;

  eNewSym = eNew->Sym;

  if( eDst->Lface != eOrg->Lface ) {
    /* We are connecting two disjoint loops -- destroy eDst->Lface */
    joiningLoops = TRUE;
    KillFace( eDst->Lface, eOrg->Lface );
  }

  /* Connect the new edge appropriately */
  Splice( eNew, eOrg->Lnext );
  Splice( eNewSym, eDst );

  /* Set the vertex and face information */
  eNew->Org = eOrg->Dst;
  eNewSym->Org = eDst->Org;
  eNew->Lface = eNewSym->Lface = eOrg->Lface;

  /* Make sure the old face points to a valid half-edge */
  eOrg->Lface->anEdge = eNewSym;

  if( ! joiningLoops ) {
    GLUface *newFace= allocFace();
    if (newFace == NULL) return NULL;

    /* We split one loop into two -- the new loop is eNew->Lface */
    MakeFace( newFace, eNew, eOrg->Lface );
  }
  return eNew;
}