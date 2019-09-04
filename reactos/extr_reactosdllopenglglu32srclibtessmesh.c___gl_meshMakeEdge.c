#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* Sym; } ;
struct TYPE_8__ {int /*<<< orphan*/  fHead; int /*<<< orphan*/  vHead; int /*<<< orphan*/  eHead; } ;
typedef  int /*<<< orphan*/  GLUvertex ;
typedef  TYPE_1__ GLUmesh ;
typedef  TYPE_2__ GLUhalfEdge ;
typedef  int /*<<< orphan*/  GLUface ;

/* Variables and functions */
 TYPE_2__* MakeEdge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeFace (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeVertex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * allocFace () ; 
 int /*<<< orphan*/ * allocVertex () ; 
 int /*<<< orphan*/  memFree (int /*<<< orphan*/ *) ; 

GLUhalfEdge *__gl_meshMakeEdge( GLUmesh *mesh )
{
  GLUvertex *newVertex1= allocVertex();
  GLUvertex *newVertex2= allocVertex();
  GLUface *newFace= allocFace();
  GLUhalfEdge *e;

  /* if any one is null then all get freed */
  if (newVertex1 == NULL || newVertex2 == NULL || newFace == NULL) {
     if (newVertex1 != NULL) memFree(newVertex1);
     if (newVertex2 != NULL) memFree(newVertex2);
     if (newFace != NULL) memFree(newFace);     
     return NULL;
  } 

  e = MakeEdge( &mesh->eHead );
  if (e == NULL) {
     memFree(newVertex1);
     memFree(newVertex2);
     memFree(newFace);
     return NULL;
  }

  MakeVertex( newVertex1, e, &mesh->vHead );
  MakeVertex( newVertex2, e->Sym, &mesh->vHead );
  MakeFace( newFace, e, &mesh->fHead );
  return e;
}