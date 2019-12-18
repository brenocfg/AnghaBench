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
typedef  size_t ptrdiff_t ;
struct TYPE_5__ {TYPE_2__* bpropcache; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_6__ {scalar_t__ key; int mode; } ;
typedef  scalar_t__ IRRef1 ;
typedef  int IRRef ;
typedef  TYPE_2__ BPropEntry ;

/* Variables and functions */
 size_t BPROP_SLOTS ; 
 int IRCONV_MODEMASK ; 

__attribute__((used)) static BPropEntry *narrow_bpc_get(jit_State *J, IRRef1 key, IRRef mode)
{
  ptrdiff_t i;
  for (i = 0; i < BPROP_SLOTS; i++) {
    BPropEntry *bp = &J->bpropcache[i];
    /* Stronger checks are ok, too. */
    if (bp->key == key && bp->mode >= mode &&
	((bp->mode ^ mode) & IRCONV_MODEMASK) == 0)
      return bp;
  }
  return NULL;
}