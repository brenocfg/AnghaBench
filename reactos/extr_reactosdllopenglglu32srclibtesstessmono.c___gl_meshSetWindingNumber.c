#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int winding; TYPE_2__* Lface; TYPE_1__* Rface; struct TYPE_10__* next; } ;
struct TYPE_9__ {TYPE_4__ eHead; } ;
struct TYPE_8__ {scalar_t__ inside; } ;
struct TYPE_7__ {scalar_t__ inside; } ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  TYPE_3__ GLUmesh ;
typedef  TYPE_4__ GLUhalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  __gl_meshDelete (TYPE_4__*) ; 

int __gl_meshSetWindingNumber( GLUmesh *mesh, int value,
			        GLboolean keepOnlyBoundary )
{
  GLUhalfEdge *e, *eNext;

  for( e = mesh->eHead.next; e != &mesh->eHead; e = eNext ) {
    eNext = e->next;
    if( e->Rface->inside != e->Lface->inside ) {

      /* This is a boundary edge (one side is interior, one is exterior). */
      e->winding = (e->Lface->inside) ? value : -value;
    } else {

      /* Both regions are interior, or both are exterior. */
      if( ! keepOnlyBoundary ) {
	e->winding = 0;
      } else {
	if ( !__gl_meshDelete( e ) ) return 0;
      }
    }
  }
  return 1;
}