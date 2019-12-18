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
struct TYPE_6__ {int flags; TYPE_1__* db; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Str ; 
 int MEM_Term ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int vdbeMemAddTerminator (TYPE_2__*) ; 

int sqlite3VdbeMemNulTerminate(Mem *pMem){
  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
  testcase( (pMem->flags & (MEM_Term|MEM_Str))==(MEM_Term|MEM_Str) );
  testcase( (pMem->flags & (MEM_Term|MEM_Str))==0 );
  if( (pMem->flags & (MEM_Term|MEM_Str))!=MEM_Str ){
    return SQLITE_OK;   /* Nothing to do */
  }else{
    return vdbeMemAddTerminator(pMem);
  }
}