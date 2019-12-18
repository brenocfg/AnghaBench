#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pRbuVfs; struct TYPE_5__* pMainRbuNext; struct TYPE_5__* pMainNext; } ;
typedef  TYPE_2__ rbu_file ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_2__* pMainRbu; TYPE_2__* pMain; } ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbuMainlistRemove(rbu_file *p){
  rbu_file **pp;
  sqlite3_mutex_enter(p->pRbuVfs->mutex);
  for(pp=&p->pRbuVfs->pMain; *pp && *pp!=p; pp=&((*pp)->pMainNext)){}
  if( *pp ) *pp = p->pMainNext;
  p->pMainNext = 0;
  for(pp=&p->pRbuVfs->pMainRbu; *pp && *pp!=p; pp=&((*pp)->pMainRbuNext)){}
  if( *pp ) *pp = p->pMainRbuNext;
  p->pMainRbuNext = 0;
  sqlite3_mutex_leave(p->pRbuVfs->mutex);
}