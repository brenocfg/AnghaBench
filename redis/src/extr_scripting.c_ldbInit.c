#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cbuf; scalar_t__ lines; int /*<<< orphan*/ * src; void* children; void* logs; scalar_t__ active; int /*<<< orphan*/ * conn; } ;

/* Variables and functions */
 TYPE_1__ ldb ; 
 void* listCreate () ; 
 int /*<<< orphan*/  listSetFreeMethod (void*,void (*) (void*)) ; 
 int /*<<< orphan*/  sdsempty () ; 
 scalar_t__ sdsfree ; 

void ldbInit(void) {
    ldb.conn = NULL;
    ldb.active = 0;
    ldb.logs = listCreate();
    listSetFreeMethod(ldb.logs,(void (*)(void*))sdsfree);
    ldb.children = listCreate();
    ldb.src = NULL;
    ldb.lines = 0;
    ldb.cbuf = sdsempty();
}