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
struct TYPE_7__ {TYPE_1__* eUp; int /*<<< orphan*/  fixUpperEdge; } ;
struct TYPE_6__ {TYPE_2__* activeRegion; } ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  TYPE_2__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  __gl_meshDelete (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FixUpperEdge( ActiveRegion *reg, GLUhalfEdge *newEdge )
/*
 * Replace an upper edge which needs fixing (see ConnectRightVertex).
 */
{
  assert( reg->fixUpperEdge );
  if ( !__gl_meshDelete( reg->eUp ) ) return 0;
  reg->fixUpperEdge = FALSE;
  reg->eUp = newEdge;
  newEdge->activeRegion = reg;

  return 1;
}