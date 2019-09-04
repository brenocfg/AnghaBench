#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* prev; TYPE_1__* anEdge; } ;
struct TYPE_6__ {struct TYPE_6__* Lnext; TYPE_2__* Lface; } ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  TYPE_2__ GLUface ;

/* Variables and functions */
 int /*<<< orphan*/  memFree (TYPE_2__*) ; 

__attribute__((used)) static void KillFace( GLUface *fDel, GLUface *newLface )
{
  GLUhalfEdge *e, *eStart = fDel->anEdge;
  GLUface *fPrev, *fNext;

  /* change the left face of all affected edges */
  e = eStart;
  do {
    e->Lface = newLface;
    e = e->Lnext;
  } while( e != eStart );

  /* delete from circular doubly-linked list */
  fPrev = fDel->prev;
  fNext = fDel->next;
  fNext->prev = fPrev;
  fPrev->next = fNext;

  memFree( fDel );
}