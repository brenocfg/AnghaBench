#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eType; int /*<<< orphan*/  pReal; } ;
typedef  TYPE_2__ sqlite3_mutex ;
struct TYPE_6__ {int /*<<< orphan*/  (* xMutexFree ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__ m; int /*<<< orphan*/  isInit; } ;

/* Variables and functions */
 scalar_t__ SQLITE_MUTEX_FAST ; 
 scalar_t__ SQLITE_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_3__ g ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void counterMutexFree(sqlite3_mutex *p){
  assert( g.isInit );
  g.m.xMutexFree(p->pReal);
  if( p->eType==SQLITE_MUTEX_FAST || p->eType==SQLITE_MUTEX_RECURSIVE ){
    free(p);
  }
}