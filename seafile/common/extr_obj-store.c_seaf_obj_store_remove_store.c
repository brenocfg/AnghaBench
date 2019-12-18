#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SeafObjStore {TYPE_1__* bend; } ;
struct TYPE_3__ {int (* remove_store ) (TYPE_1__*,char const*) ;} ;
typedef  TYPE_1__ ObjBackend ;

/* Variables and functions */
 int stub1 (TYPE_1__*,char const*) ; 

int
seaf_obj_store_remove_store (struct SeafObjStore *obj_store,
                             const char *store_id)
{
    ObjBackend *bend = obj_store->bend;

    return bend->remove_store (bend, store_id);
}