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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_2__ {int nMaxFrame; int /*<<< orphan*/  eMode; } ;
typedef  TYPE_1__ CheckpointStarvationCtx ;

/* Variables and functions */
 int CHECKPOINT_STARVATION_FRAMELIMIT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_wal_checkpoint_v2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkpoint_starvation_walhook(
  void *pCtx, 
  sqlite3 *db, 
  const char *zDb, 
  int nFrame
){
  CheckpointStarvationCtx *p = (CheckpointStarvationCtx *)pCtx;
  if( nFrame>p->nMaxFrame ){
    p->nMaxFrame = nFrame;
  }
  if( nFrame>=CHECKPOINT_STARVATION_FRAMELIMIT ){
    sqlite3_wal_checkpoint_v2(db, zDb, p->eMode, 0, 0);
  }
  return SQLITE_OK;
}