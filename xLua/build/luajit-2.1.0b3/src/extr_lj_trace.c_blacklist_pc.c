#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ GCproto ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ BC_ILOOP ; 
 scalar_t__ BC_LOOP ; 
 int /*<<< orphan*/  PROTO_ILOOP ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbc_op (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void blacklist_pc(GCproto *pt, BCIns *pc)
{
  setbc_op(pc, (int)bc_op(*pc)+(int)BC_ILOOP-(int)BC_LOOP);
  pt->flags |= PROTO_ILOOP;
}