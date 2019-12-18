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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {int /*<<< orphan*/  pIndex; } ;
typedef  TYPE_1__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5IndexIter ;

/* Variables and functions */
 int fts5IndexReturn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5MultiIterNextFrom (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

int sqlite3Fts5IterNextFrom(Fts5IndexIter *pIndexIter, i64 iMatch){
  Fts5Iter *pIter = (Fts5Iter*)pIndexIter;
  fts5MultiIterNextFrom(pIter->pIndex, pIter, iMatch);
  return fts5IndexReturn(pIter->pIndex);
}