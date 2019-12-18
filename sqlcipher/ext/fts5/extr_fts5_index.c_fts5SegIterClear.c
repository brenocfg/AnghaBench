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
struct TYPE_4__ {int /*<<< orphan*/  aRowidOffset; int /*<<< orphan*/  pDlidx; int /*<<< orphan*/  pNextLeaf; int /*<<< orphan*/  pLeaf; int /*<<< orphan*/  term; } ;
typedef  TYPE_1__ Fts5SegIter ;

/* Variables and functions */
 int /*<<< orphan*/  fts5BufferFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5DataRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5DlidxIterFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5SegIterClear(Fts5SegIter *pIter){
  fts5BufferFree(&pIter->term);
  fts5DataRelease(pIter->pLeaf);
  fts5DataRelease(pIter->pNextLeaf);
  fts5DlidxIterFree(pIter->pDlidx);
  sqlite3_free(pIter->aRowidOffset);
  memset(pIter, 0, sizeof(Fts5SegIter));
}