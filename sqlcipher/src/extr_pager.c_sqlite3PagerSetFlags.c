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
struct TYPE_3__ {int noSync; int fullSync; int extraSync; int syncFlags; int walSyncFlags; int /*<<< orphan*/  doNotSpill; scalar_t__ tempFile; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 unsigned int PAGER_CACHESPILL ; 
 unsigned int PAGER_CKPT_FULLFSYNC ; 
 unsigned int PAGER_FULLFSYNC ; 
 unsigned int PAGER_SYNCHRONOUS_EXTRA ; 
 unsigned int PAGER_SYNCHRONOUS_FULL ; 
 unsigned int PAGER_SYNCHRONOUS_MASK ; 
 unsigned int PAGER_SYNCHRONOUS_OFF ; 
 int /*<<< orphan*/  SPILLFLAG_OFF ; 
 int SQLITE_SYNC_FULL ; 
 int SQLITE_SYNC_NORMAL ; 

void sqlite3PagerSetFlags(
  Pager *pPager,        /* The pager to set safety level for */
  unsigned pgFlags      /* Various flags */
){
  unsigned level = pgFlags & PAGER_SYNCHRONOUS_MASK;
  if( pPager->tempFile ){
    pPager->noSync = 1;
    pPager->fullSync = 0;
    pPager->extraSync = 0;
  }else{
    pPager->noSync =  level==PAGER_SYNCHRONOUS_OFF ?1:0;
    pPager->fullSync = level>=PAGER_SYNCHRONOUS_FULL ?1:0;
    pPager->extraSync = level==PAGER_SYNCHRONOUS_EXTRA ?1:0;
  }
  if( pPager->noSync ){
    pPager->syncFlags = 0;
  }else if( pgFlags & PAGER_FULLFSYNC ){
    pPager->syncFlags = SQLITE_SYNC_FULL;
  }else{
    pPager->syncFlags = SQLITE_SYNC_NORMAL;
  }
  pPager->walSyncFlags = (pPager->syncFlags<<2);
  if( pPager->fullSync ){
    pPager->walSyncFlags |= pPager->syncFlags;
  }
  if( (pgFlags & PAGER_CKPT_FULLFSYNC) && !pPager->noSync ){
    pPager->walSyncFlags |= (SQLITE_SYNC_FULL<<2);
  }
  if( pgFlags & PAGER_CACHESPILL ){
    pPager->doNotSpill &= ~SPILLFLAG_OFF;
  }else{
    pPager->doNotSpill |= SPILLFLAG_OFF;
  }
}