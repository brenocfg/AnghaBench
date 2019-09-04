#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_13__ {int /*<<< orphan*/  value; TYPE_3__* type; } ;
typedef  TYPE_2__ moduleValue ;
struct TYPE_14__ {int /*<<< orphan*/  (* aof_rewrite ) (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ moduleType ;
struct TYPE_15__ {scalar_t__ error; scalar_t__ ctx; } ;
typedef  TYPE_4__ RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  moduleFreeContext (scalar_t__) ; 
 int /*<<< orphan*/  moduleInitIOContext (TYPE_4__,TYPE_3__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (scalar_t__) ; 

int rewriteModuleObject(rio *r, robj *key, robj *o) {
    RedisModuleIO io;
    moduleValue *mv = o->ptr;
    moduleType *mt = mv->type;
    moduleInitIOContext(io,mt,r,key);
    mt->aof_rewrite(&io,key,mv->value);
    if (io.ctx) {
        moduleFreeContext(io.ctx);
        zfree(io.ctx);
    }
    return io.error ? 0 : 1;
}