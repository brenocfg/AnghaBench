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
struct TYPE_3__ {int (* xSize ) (void*) ;} ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMTYPE_HEAP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3MemdebugHasType (void*,int /*<<< orphan*/ ) ; 
 int stub1 (void*) ; 

int sqlite3MallocSize(void *p){
  assert( sqlite3MemdebugHasType(p, MEMTYPE_HEAP) );
  return sqlite3GlobalConfig.m.xSize(p);
}