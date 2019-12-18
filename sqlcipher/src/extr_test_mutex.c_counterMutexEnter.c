#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t eType; int /*<<< orphan*/  pReal; } ;
typedef  TYPE_2__ sqlite3_mutex ;
struct TYPE_5__ {int /*<<< orphan*/  (* xMutexEnter ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int isInit; TYPE_1__ m; int /*<<< orphan*/ * aCounter; } ;

/* Variables and functions */
 size_t MAX_MUTEXES ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ g ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void counterMutexEnter(sqlite3_mutex *p){
  assert( g.isInit );
  assert( p->eType>=0 );
  assert( p->eType<MAX_MUTEXES );
  g.aCounter[p->eType]++;
  g.m.xMutexEnter(p->pReal);
}