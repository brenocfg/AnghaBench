#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pDummy; scalar_t__ nInstance; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 TYPE_1__ testpcacheGlobal ; 

__attribute__((used)) static void testpcacheShutdown(void *pArg){
  assert( pArg==(void*)&testpcacheGlobal );
  assert( testpcacheGlobal.pDummy!=0 );
  assert( testpcacheGlobal.nInstance==0 );
  sqlite3_free( testpcacheGlobal.pDummy );
  testpcacheGlobal.pDummy = 0;
}