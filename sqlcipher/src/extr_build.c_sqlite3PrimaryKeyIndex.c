#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pIndex; } ;
typedef  TYPE_1__ Table ;
struct TYPE_7__ {struct TYPE_7__* pNext; } ;
typedef  TYPE_2__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  IsPrimaryKeyIndex (TYPE_2__*) ; 

Index *sqlite3PrimaryKeyIndex(Table *pTab){
  Index *p;
  for(p=pTab->pIndex; p && !IsPrimaryKeyIndex(p); p=p->pNext){}
  return p;
}