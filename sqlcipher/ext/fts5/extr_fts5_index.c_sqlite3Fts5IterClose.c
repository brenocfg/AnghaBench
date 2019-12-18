#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pIndex; } ;
typedef  TYPE_1__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5IndexIter ;
typedef  int /*<<< orphan*/  Fts5Index ;

/* Variables and functions */
 int /*<<< orphan*/  fts5CloseReader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5MultiIterFree (TYPE_1__*) ; 

void sqlite3Fts5IterClose(Fts5IndexIter *pIndexIter){
  if( pIndexIter ){
    Fts5Iter *pIter = (Fts5Iter*)pIndexIter;
    Fts5Index *pIndex = pIter->pIndex;
    fts5MultiIterFree(pIter);
    fts5CloseReader(pIndex);
  }
}