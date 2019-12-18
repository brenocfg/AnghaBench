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
struct TYPE_7__ {TYPE_1__* ir; } ;
struct TYPE_6__ {scalar_t__ o; size_t op1; } ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ GCtrace ;

/* Variables and functions */
 scalar_t__ IR_AREF ; 
 scalar_t__ IR_ASTORE ; 
 scalar_t__ IR_FSTORE ; 
 scalar_t__ IR_HREFK ; 
 scalar_t__ IR_HSTORE ; 
 scalar_t__ IR_XSTORE ; 

__attribute__((used)) static int snap_sunk_store2(GCtrace *T, IRIns *ira, IRIns *irs)
{
  if (irs->o == IR_ASTORE || irs->o == IR_HSTORE ||
      irs->o == IR_FSTORE || irs->o == IR_XSTORE) {
    IRIns *irk = &T->ir[irs->op1];
    if (irk->o == IR_AREF || irk->o == IR_HREFK)
      irk = &T->ir[irk->op1];
    return (&T->ir[irk->op1] == ira);
  }
  return 0;
}