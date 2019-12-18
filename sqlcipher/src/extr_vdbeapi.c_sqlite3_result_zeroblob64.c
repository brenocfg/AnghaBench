#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_7__ {TYPE_3__* pOut; } ;
typedef  TYPE_2__ sqlite3_context ;
struct TYPE_8__ {TYPE_1__* db; } ;
struct TYPE_6__ {scalar_t__* aLimit; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 size_t SQLITE_LIMIT_LENGTH ; 
 int SQLITE_OK ; 
 int SQLITE_TOOBIG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetZeroBlob (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

int sqlite3_result_zeroblob64(sqlite3_context *pCtx, u64 n){
  Mem *pOut = pCtx->pOut;
  assert( sqlite3_mutex_held(pOut->db->mutex) );
  if( n>(u64)pOut->db->aLimit[SQLITE_LIMIT_LENGTH] ){
    return SQLITE_TOOBIG;
  }
  sqlite3VdbeMemSetZeroBlob(pCtx->pOut, (int)n);
  return SQLITE_OK;
}