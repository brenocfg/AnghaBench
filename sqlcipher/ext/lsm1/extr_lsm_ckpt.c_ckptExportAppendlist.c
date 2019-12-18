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
struct TYPE_5__ {TYPE_1__* pWorker; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_4__ {int /*<<< orphan*/ * aiAppend; } ;
typedef  int /*<<< orphan*/  LsmPgno ;
typedef  int /*<<< orphan*/  CkptBuffer ;

/* Variables and functions */
 int LSM_APPLIST_SZ ; 
 int /*<<< orphan*/  ckptAppend64 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ckptExportAppendlist(
  lsm_db *db,                     /* Database connection */
  CkptBuffer *p,                  /* Checkpoint buffer to write to */
  int *piOut,                     /* IN/OUT: Offset within checkpoint buffer */
  int *pRc                        /* IN/OUT: Error code */
){
  int i;
  LsmPgno *aiAppend = db->pWorker->aiAppend;

  for(i=0; i<LSM_APPLIST_SZ; i++){
    ckptAppend64(p, piOut, aiAppend[i], pRc);
  }
}