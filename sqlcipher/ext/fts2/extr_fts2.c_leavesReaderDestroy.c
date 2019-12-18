#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int idx; int /*<<< orphan*/  rootData; int /*<<< orphan*/  leafReader; int /*<<< orphan*/ * pStmt; } ;
typedef  TYPE_1__ LeavesReader ;

/* Variables and functions */
 int /*<<< orphan*/  SCRAMBLE (TYPE_1__*) ; 
 int /*<<< orphan*/  dataBufferDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leafReaderDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void leavesReaderDestroy(LeavesReader *pReader){
  /* If idx is -1, that means we're using a non-cached statement
  ** handle in the optimize() case, so we need to release it.
  */
  if( pReader->pStmt!=NULL && pReader->idx==-1 ){
    sqlite3_finalize(pReader->pStmt);
  }
  leafReaderDestroy(&pReader->leafReader);
  dataBufferDestroy(&pReader->rootData);
  SCRAMBLE(pReader);
}