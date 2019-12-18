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
struct TYPE_3__ {int /*<<< orphan*/ * pDirty; } ;
typedef  int /*<<< orphan*/  PgHdr ;
typedef  TYPE_1__ PCache ;

/* Variables and functions */
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 int /*<<< orphan*/  sqlite3PcacheMakeClean (int /*<<< orphan*/ *) ; 

void sqlite3PcacheCleanAll(PCache *pCache){
  PgHdr *p;
  pcacheTrace(("%p.CLEAN-ALL\n",pCache));
  while( (p = pCache->pDirty)!=0 ){
    sqlite3PcacheMakeClean(p);
  }
}