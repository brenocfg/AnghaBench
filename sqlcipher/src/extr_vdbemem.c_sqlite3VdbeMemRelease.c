#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ szMalloc; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 scalar_t__ VdbeMemDynamic (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeCheckMemInvariants (TYPE_1__*) ; 
 int /*<<< orphan*/  vdbeMemClear (TYPE_1__*) ; 

void sqlite3VdbeMemRelease(Mem *p){
  assert( sqlite3VdbeCheckMemInvariants(p) );
  if( VdbeMemDynamic(p) || p->szMalloc ){
    vdbeMemClear(p);
  }
}