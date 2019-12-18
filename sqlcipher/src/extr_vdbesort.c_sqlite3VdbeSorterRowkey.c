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
typedef  int /*<<< orphan*/  VdbeSorter ;
struct TYPE_8__ {int /*<<< orphan*/ * pSorter; } ;
struct TYPE_9__ {scalar_t__ eCurType; TYPE_1__ uc; } ;
typedef  TYPE_2__ VdbeCursor ;
struct TYPE_10__ {int n; int /*<<< orphan*/  z; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 scalar_t__ CURTYPE_SORTER ; 
 int /*<<< orphan*/  MEM_Blob ; 
 int /*<<< orphan*/  MemSetTypeFlag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ sqlite3VdbeMemClearAndResize (TYPE_3__*,int) ; 
 void* vdbeSorterRowkey (int /*<<< orphan*/ *,int*) ; 

int sqlite3VdbeSorterRowkey(const VdbeCursor *pCsr, Mem *pOut){
  VdbeSorter *pSorter;
  void *pKey; int nKey;           /* Sorter key to copy into pOut */

  assert( pCsr->eCurType==CURTYPE_SORTER );
  pSorter = pCsr->uc.pSorter;
  pKey = vdbeSorterRowkey(pSorter, &nKey);
  if( sqlite3VdbeMemClearAndResize(pOut, nKey) ){
    return SQLITE_NOMEM_BKPT;
  }
  pOut->n = nKey;
  MemSetTypeFlag(pOut, MEM_Blob);
  memcpy(pOut->z, pKey, nKey);

  return SQLITE_OK;
}