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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_6__ {int /*<<< orphan*/  i; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; TYPE_1__ u; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Int ; 
 scalar_t__ VdbeMemDynamic (TYPE_2__*) ; 
 int /*<<< orphan*/  vdbeReleaseAndSetInt64 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void sqlite3VdbeMemSetInt64(Mem *pMem, i64 val){
  if( VdbeMemDynamic(pMem) ){
    vdbeReleaseAndSetInt64(pMem, val);
  }else{
    pMem->u.i = val;
    pMem->flags = MEM_Int;
  }
}