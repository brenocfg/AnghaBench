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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {struct TYPE_4__* pNextWin; } ;
typedef  TYPE_1__ Window ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3WindowDelete (int /*<<< orphan*/ *,TYPE_1__*) ; 

void sqlite3WindowListDelete(sqlite3 *db, Window *p){
  while( p ){
    Window *pNext = p->pNextWin;
    sqlite3WindowDelete(db, p);
    p = pNext;
  }
}