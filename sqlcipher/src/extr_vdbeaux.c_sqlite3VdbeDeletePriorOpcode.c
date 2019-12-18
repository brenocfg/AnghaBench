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
typedef  scalar_t__ u8 ;
struct TYPE_6__ {int nOp; TYPE_1__* aOp; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_5__ {scalar_t__ opcode; } ;

/* Variables and functions */
 int sqlite3VdbeChangeToNoop (TYPE_2__*,int) ; 

int sqlite3VdbeDeletePriorOpcode(Vdbe *p, u8 op){
  if( p->nOp>0 && p->aOp[p->nOp-1].opcode==op ){
    return sqlite3VdbeChangeToNoop(p, p->nOp-1);
  }else{
    return 0;
  }
}