#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* pOut; } ;
typedef  TYPE_2__ sqlite3_context ;
struct TYPE_9__ {int /*<<< orphan*/  flags; TYPE_1__* db; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Null ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetPointer (TYPE_3__*,void*,char const*,void (*) (void*)) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3_result_pointer(
  sqlite3_context *pCtx,
  void *pPtr,
  const char *zPType,
  void (*xDestructor)(void*)
){
  Mem *pOut = pCtx->pOut;
  assert( sqlite3_mutex_held(pOut->db->mutex) );
  sqlite3VdbeMemRelease(pOut);
  pOut->flags = MEM_Null;
  sqlite3VdbeMemSetPointer(pOut, pPtr, zPType, xDestructor);
}