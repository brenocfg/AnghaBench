#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* pRule; } ;
typedef  TYPE_1__ amatch_vtab ;
struct TYPE_6__ {struct TYPE_6__* pNext; } ;
typedef  TYPE_2__ amatch_rule ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void amatchFreeRules(amatch_vtab *p){
  while( p->pRule ){
    amatch_rule *pRule = p->pRule;
    p->pRule = pRule->pNext;
    sqlite3_free(pRule);
  }
  p->pRule = 0;
}