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
struct TYPE_3__ {int bEof; int /*<<< orphan*/  iPos; int /*<<< orphan*/  i; int /*<<< orphan*/  n; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ Fts5PoslistReader ;

/* Variables and functions */
 scalar_t__ sqlite3Fts5PoslistNext64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int sqlite3Fts5PoslistReaderNext(Fts5PoslistReader *pIter){
  if( sqlite3Fts5PoslistNext64(pIter->a, pIter->n, &pIter->i, &pIter->iPos) ){
    pIter->bEof = 1;
  }
  return pIter->bEof;
}