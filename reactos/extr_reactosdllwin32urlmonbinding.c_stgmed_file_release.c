#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stgmed_obj_t ;
struct TYPE_5__ {TYPE_1__* buf; } ;
typedef  TYPE_2__ stgmed_file_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/  IUnknown_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

__attribute__((used)) static void stgmed_file_release(stgmed_obj_t *obj)
{
    stgmed_file_obj_t *file_obj = (stgmed_file_obj_t*)obj;

    IUnknown_Release(&file_obj->buf->IUnknown_iface);
    heap_free(file_obj);
}