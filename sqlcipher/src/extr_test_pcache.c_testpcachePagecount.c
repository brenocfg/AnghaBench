#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ iMagic; int nFree; } ;
typedef  TYPE_1__ testpcache ;
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_4__ {scalar_t__ pDummy; scalar_t__ nInstance; } ;

/* Variables and functions */
 int TESTPCACHE_NPAGE ; 
 scalar_t__ TESTPCACHE_VALID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ testpcacheGlobal ; 

__attribute__((used)) static int testpcachePagecount(sqlite3_pcache *pCache){
  testpcache *p = (testpcache*)pCache;
  assert( p->iMagic==TESTPCACHE_VALID );
  assert( testpcacheGlobal.pDummy!=0 );
  assert( testpcacheGlobal.nInstance>0 );
  return TESTPCACHE_NPAGE - p->nFree;
}