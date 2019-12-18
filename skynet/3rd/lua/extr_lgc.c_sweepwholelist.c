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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ GCObject ;

/* Variables and functions */
 int /*<<< orphan*/  freeobj (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void sweepwholelist (lua_State *L, GCObject **p) {
  while (*p != NULL) {
    GCObject *curr = *p;
    *p = curr->next;  /* remove 'curr' from list */
    freeobj(L, curr);  /* erase 'curr' */
   }
}