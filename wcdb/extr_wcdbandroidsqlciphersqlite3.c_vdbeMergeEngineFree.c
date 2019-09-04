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
struct TYPE_4__ {int nTree; int /*<<< orphan*/ * aReadr; } ;
typedef  TYPE_1__ MergeEngine ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vdbePmaReaderClear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vdbeMergeEngineFree(MergeEngine *pMerger){
  int i;
  if( pMerger ){
    for(i=0; i<pMerger->nTree; i++){
      vdbePmaReaderClear(&pMerger->aReadr[i]);
    }
  }
  sqlite3_free(pMerger);
}