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
struct TYPE_6__ {int /*<<< orphan*/  inside; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__ fHead; } ;
typedef  TYPE_1__ GLUmesh ;
typedef  TYPE_2__ GLUface ;

/* Variables and functions */
 int /*<<< orphan*/  __gl_meshZapFace (TYPE_2__*) ; 

void __gl_meshDiscardExterior( GLUmesh *mesh )
{
  GLUface *f, *next;

  /*LINTED*/
  for( f = mesh->fHead.next; f != &mesh->fHead; f = next ) {
    /* Since f will be destroyed, save its next pointer. */
    next = f->next;
    if( ! f->inside ) {
      __gl_meshZapFace( f );
    }
  }
}