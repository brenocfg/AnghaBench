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
struct TYPE_4__ {int /*<<< orphan*/  pScan; } ;
typedef  TYPE_1__ Fts5Hash ;

/* Variables and functions */
 int fts5HashEntrySort (TYPE_1__*,char const*,int,int /*<<< orphan*/ *) ; 

int sqlite3Fts5HashScanInit(
  Fts5Hash *p,                    /* Hash table to query */
  const char *pTerm, int nTerm    /* Query prefix */
){
  return fts5HashEntrySort(p, pTerm, nTerm, &p->pScan);
}