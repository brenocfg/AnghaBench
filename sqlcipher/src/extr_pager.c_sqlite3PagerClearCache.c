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
struct TYPE_4__ {scalar_t__ tempFile; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ MEMDB ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pager_reset (TYPE_1__*) ; 

void sqlite3PagerClearCache(Pager *pPager){
  assert( MEMDB==0 || pPager->tempFile );
  if( pPager->tempFile==0 ) pager_reset(pPager);
}