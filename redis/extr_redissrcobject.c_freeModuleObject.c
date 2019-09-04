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
struct TYPE_7__ {TYPE_3__* ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_8__ {int /*<<< orphan*/  value; TYPE_1__* type; } ;
typedef  TYPE_3__ moduleValue ;
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_3__*) ; 

void freeModuleObject(robj *o) {
    moduleValue *mv = o->ptr;
    mv->type->free(mv->value);
    zfree(mv);
}