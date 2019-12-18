#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* pOut; } ;
typedef  TYPE_2__ sqlite3_context ;
struct TYPE_7__ {TYPE_1__* db; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetZeroBlob (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3_result_zeroblob(sqlite3_context *pCtx, int n){
  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
  sqlite3VdbeMemSetZeroBlob(pCtx->pOut, n);
}