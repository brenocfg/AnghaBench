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
typedef  int /*<<< orphan*/  robj ;
struct TYPE_4__ {void* value; int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ moduleValue ;
typedef  int /*<<< orphan*/  moduleType ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_MODULE ; 
 int /*<<< orphan*/ * createObject (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* zmalloc (int) ; 

robj *createModuleObject(moduleType *mt, void *value) {
    moduleValue *mv = zmalloc(sizeof(*mv));
    mv->type = mt;
    mv->value = value;
    return createObject(OBJ_MODULE,mv);
}