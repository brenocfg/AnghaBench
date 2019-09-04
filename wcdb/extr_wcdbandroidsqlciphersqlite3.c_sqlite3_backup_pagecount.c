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
struct TYPE_3__ {int nPagecount; } ;
typedef  TYPE_1__ sqlite3_backup ;

/* Variables and functions */

int sqlite3_backup_pagecount(sqlite3_backup *p){
#ifdef SQLITE_ENABLE_API_ARMOR
  if( p==0 ){
    (void)SQLITE_MISUSE_BKPT;
    return 0;
  }
#endif
  return p->nPagecount;
}