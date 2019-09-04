#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * vtbl; } ;
typedef  TYPE_1__ stgmed_obj_t ;
struct TYPE_8__ {TYPE_1__ stgmed_obj; TYPE_3__* buf; } ;
typedef  TYPE_2__ stgmed_file_obj_t ;
struct TYPE_9__ {int /*<<< orphan*/  IUnknown_iface; } ;
typedef  TYPE_3__ stgmed_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  stgmed_file_vtbl ; 

__attribute__((used)) static stgmed_obj_t *create_stgmed_file(stgmed_buf_t *buf)
{
    stgmed_file_obj_t *ret = heap_alloc(sizeof(*ret));

    ret->stgmed_obj.vtbl = &stgmed_file_vtbl;

    IUnknown_AddRef(&buf->IUnknown_iface);
    ret->buf = buf;

    return &ret->stgmed_obj;
}