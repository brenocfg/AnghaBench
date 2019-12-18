#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {void (* xWriteHook ) (void*,int,lsm_i64,int,int) ;void* pWriteCtx; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 scalar_t__ tdb_lsm (int /*<<< orphan*/ *) ; 

void tdb_lsm_write_hook(
  TestDb *pDb, 
  void (*xWrite)(void *, int, lsm_i64, int, int),
  void *pWriteCtx
){
  if( tdb_lsm(pDb) ){
    LsmDb *p = (LsmDb *)pDb;
    p->xWriteHook = xWrite;
    p->pWriteCtx = pWriteCtx;
  }
}