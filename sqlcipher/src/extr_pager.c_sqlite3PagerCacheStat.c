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
struct TYPE_3__ {scalar_t__* aStat; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_STAT_HIT ; 
 int PAGER_STAT_MISS ; 
 int PAGER_STAT_SPILL ; 
 int PAGER_STAT_WRITE ; 
 int SQLITE_DBSTATUS_CACHE_HIT ; 
 int SQLITE_DBSTATUS_CACHE_MISS ; 
 int SQLITE_DBSTATUS_CACHE_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 

void sqlite3PagerCacheStat(Pager *pPager, int eStat, int reset, int *pnVal){

  assert( eStat==SQLITE_DBSTATUS_CACHE_HIT
       || eStat==SQLITE_DBSTATUS_CACHE_MISS
       || eStat==SQLITE_DBSTATUS_CACHE_WRITE
       || eStat==SQLITE_DBSTATUS_CACHE_WRITE+1
  );

  assert( SQLITE_DBSTATUS_CACHE_HIT+1==SQLITE_DBSTATUS_CACHE_MISS );
  assert( SQLITE_DBSTATUS_CACHE_HIT+2==SQLITE_DBSTATUS_CACHE_WRITE );
  assert( PAGER_STAT_HIT==0 && PAGER_STAT_MISS==1
           && PAGER_STAT_WRITE==2 && PAGER_STAT_SPILL==3 );

  eStat -= SQLITE_DBSTATUS_CACHE_HIT;
  *pnVal += pPager->aStat[eStat];
  if( reset ){
    pPager->aStat[eStat] = 0;
  }
}