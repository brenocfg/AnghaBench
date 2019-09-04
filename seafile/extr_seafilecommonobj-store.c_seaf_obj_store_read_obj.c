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
struct TYPE_3__ {int (* read ) (TYPE_1__*,char const*,int,char const*,void**,int*) ;} ;
typedef  TYPE_1__ ObjBackend ;

/* Variables and functions */
 int /*<<< orphan*/  is_object_id_valid (char const*) ; 
 int /*<<< orphan*/  is_uuid_valid (char const*) ; 
 int stub1 (TYPE_1__*,char const*,int,char const*,void**,int*) ; 

int
seaf_obj_store_read_obj (struct SeafObjStore *obj_store,
                         const char *repo_id,
                         int version,
                         const char *obj_id,
                         void **data,
                         int *len)
{
    ObjBackend *bend = obj_store->bend;

    if (!repo_id || !is_uuid_valid(repo_id) ||
        !obj_id || !is_object_id_valid(obj_id))
        return -1;

    return bend->read (bend, repo_id, version, obj_id, data, len);
}