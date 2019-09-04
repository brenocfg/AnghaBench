#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * activeRegion; scalar_t__ winding; int /*<<< orphan*/ * Lface; int /*<<< orphan*/ * Org; struct TYPE_5__* Lnext; struct TYPE_5__* Onext; struct TYPE_5__* Sym; struct TYPE_5__* next; } ;
struct TYPE_6__ {TYPE_1__ eSym; TYPE_1__ e; } ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  TYPE_2__ EdgePair ;

/* Variables and functions */
 scalar_t__ memAlloc (int) ; 

__attribute__((used)) static GLUhalfEdge *MakeEdge( GLUhalfEdge *eNext )
{
  GLUhalfEdge *e;
  GLUhalfEdge *eSym;
  GLUhalfEdge *ePrev;
  EdgePair *pair = (EdgePair *)memAlloc( sizeof( EdgePair ));
  if (pair == NULL) return NULL;

  e = &pair->e;
  eSym = &pair->eSym;

  /* Make sure eNext points to the first edge of the edge pair */
  if( eNext->Sym < eNext ) { eNext = eNext->Sym; }

  /* Insert in circular doubly-linked list before eNext.
   * Note that the prev pointer is stored in Sym->next.
   */
  ePrev = eNext->Sym->next;
  eSym->next = ePrev;
  ePrev->Sym->next = e;
  e->next = eNext;
  eNext->Sym->next = eSym;

  e->Sym = eSym;
  e->Onext = e;
  e->Lnext = eSym;
  e->Org = NULL;
  e->Lface = NULL;
  e->winding = 0;
  e->activeRegion = NULL;

  eSym->Sym = e;
  eSym->Onext = eSym;
  eSym->Lnext = e;
  eSym->Org = NULL;
  eSym->Lface = NULL;
  eSym->winding = 0;
  eSym->activeRegion = NULL;

  return e;
}