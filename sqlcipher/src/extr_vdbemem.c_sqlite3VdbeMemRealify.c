#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  r; } ;
struct TYPE_10__ {TYPE_2__ u; TYPE_1__* db; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int EIGHT_BYTE_ALIGNMENT (TYPE_3__*) ; 
 int /*<<< orphan*/  MEM_Real ; 
 int /*<<< orphan*/  MemSetTypeFlag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeRealValue (TYPE_3__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3VdbeMemRealify(Mem *pMem){
  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
  assert( EIGHT_BYTE_ALIGNMENT(pMem) );

  pMem->u.r = sqlite3VdbeRealValue(pMem);
  MemSetTypeFlag(pMem, MEM_Real);
  return SQLITE_OK;
}