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
struct TYPE_5__ {scalar_t__ i; } ;
struct TYPE_6__ {int flags; TYPE_1__ u; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Int ; 
 int MEM_Null ; 
 double sqlite3VdbeRealValue (TYPE_2__*) ; 

int sqlite3VdbeBooleanValue(Mem *pMem, int ifNull){
  if( pMem->flags & MEM_Int ) return pMem->u.i!=0;
  if( pMem->flags & MEM_Null ) return ifNull;
  return sqlite3VdbeRealValue(pMem)!=0.0;
}