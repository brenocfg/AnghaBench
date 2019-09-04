#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* inside; void* marked; int /*<<< orphan*/ * trail; int /*<<< orphan*/ * data; int /*<<< orphan*/ * anEdge; struct TYPE_9__* prev; struct TYPE_9__* next; } ;
struct TYPE_8__ {int /*<<< orphan*/ * activeRegion; scalar_t__ winding; int /*<<< orphan*/ * Lface; int /*<<< orphan*/ * Org; int /*<<< orphan*/ * Lnext; int /*<<< orphan*/ * Onext; struct TYPE_8__* Sym; struct TYPE_8__* next; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * anEdge; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
struct TYPE_7__ {TYPE_3__ eHeadSym; TYPE_3__ eHead; TYPE_4__ fHead; TYPE_1__ vHead; } ;
typedef  TYPE_1__ GLUvertex ;
typedef  TYPE_2__ GLUmesh ;
typedef  TYPE_3__ GLUhalfEdge ;
typedef  TYPE_4__ GLUface ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ memAlloc (int) ; 

GLUmesh *__gl_meshNewMesh( void )
{
  GLUvertex *v;
  GLUface *f;
  GLUhalfEdge *e;
  GLUhalfEdge *eSym;
  GLUmesh *mesh = (GLUmesh *)memAlloc( sizeof( GLUmesh ));
  if (mesh == NULL) {
     return NULL;
  }
  
  v = &mesh->vHead;
  f = &mesh->fHead;
  e = &mesh->eHead;
  eSym = &mesh->eHeadSym;

  v->next = v->prev = v;
  v->anEdge = NULL;
  v->data = NULL;

  f->next = f->prev = f;
  f->anEdge = NULL;
  f->data = NULL;
  f->trail = NULL;
  f->marked = FALSE;
  f->inside = FALSE;

  e->next = e;
  e->Sym = eSym;
  e->Onext = NULL;
  e->Lnext = NULL;
  e->Org = NULL;
  e->Lface = NULL;
  e->winding = 0;
  e->activeRegion = NULL;

  eSym->next = eSym;
  eSym->Sym = e;
  eSym->Onext = NULL;
  eSym->Lnext = NULL;
  eSym->Org = NULL;
  eSym->Lface = NULL;
  eSym->winding = 0;
  eSym->activeRegion = NULL;

  return mesh;
}