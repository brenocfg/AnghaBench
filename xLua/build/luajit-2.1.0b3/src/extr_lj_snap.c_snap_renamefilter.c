#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nins; TYPE_1__* ir; } ;
struct TYPE_4__ {scalar_t__ o; scalar_t__ op2; int /*<<< orphan*/  op1; } ;
typedef  scalar_t__ SnapNo ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ GCtrace ;
typedef  int /*<<< orphan*/  BloomFilter ;

/* Variables and functions */
 scalar_t__ IR_RENAME ; 
 int /*<<< orphan*/  bloomset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BloomFilter snap_renamefilter(GCtrace *T, SnapNo lim)
{
  BloomFilter rfilt = 0;
  IRIns *ir;
  for (ir = &T->ir[T->nins-1]; ir->o == IR_RENAME; ir--)
    if (ir->op2 <= lim)
      bloomset(rfilt, ir->op1);
  return rfilt;
}