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
struct TYPE_4__ {struct TYPE_4__* zIdx; struct TYPE_4__* zDataTbl; struct TYPE_4__* zTbl; } ;
typedef  TYPE_1__ RbuState ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void rbuFreeState(RbuState *p){
  if( p ){
    sqlite3_free(p->zTbl);
    sqlite3_free(p->zDataTbl);
    sqlite3_free(p->zIdx);
    sqlite3_free(p);
  }
}