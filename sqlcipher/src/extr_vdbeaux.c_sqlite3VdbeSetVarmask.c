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
typedef  int u32 ;
struct TYPE_5__ {int expmask; TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int SQLITE_EnableQPSG ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3VdbeSetVarmask(Vdbe *v, int iVar){
  assert( iVar>0 );
  assert( (v->db->flags & SQLITE_EnableQPSG)==0 );
  if( iVar>=32 ){
    v->expmask |= 0x80000000;
  }else{
    v->expmask |= ((u32)1 << (iVar-1));
  }
}