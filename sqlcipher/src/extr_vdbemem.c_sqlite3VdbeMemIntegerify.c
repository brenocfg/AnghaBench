#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  i; } ;
struct TYPE_11__ {TYPE_2__ u; TYPE_1__* db; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int EIGHT_BYTE_ALIGNMENT (TYPE_3__*) ; 
 int /*<<< orphan*/  MEM_Int ; 
 int /*<<< orphan*/  MemSetTypeFlag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeIntValue (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemIsRowSet (TYPE_3__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3VdbeMemIntegerify(Mem *pMem){
  assert( pMem->db==0 || sqlite3_mutex_held(pMem->db->mutex) );
  assert( !sqlite3VdbeMemIsRowSet(pMem) );
  assert( EIGHT_BYTE_ALIGNMENT(pMem) );

  pMem->u.i = sqlite3VdbeIntValue(pMem);
  MemSetTypeFlag(pMem, MEM_Int);
  return SQLITE_OK;
}