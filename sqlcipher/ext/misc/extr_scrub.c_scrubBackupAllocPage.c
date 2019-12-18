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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ rcErr; int /*<<< orphan*/  szPage; } ;
typedef  TYPE_1__ ScrubState ;

/* Variables and functions */
 scalar_t__ SQLITE_NOMEM ; 
 int /*<<< orphan*/ * sqlite3_malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 *scrubBackupAllocPage(ScrubState *p){
  u8 *pPage;
  if( p->rcErr ) return 0;
  pPage = sqlite3_malloc( p->szPage );
  if( pPage==0 ) p->rcErr = SQLITE_NOMEM;
  return pPage;
}