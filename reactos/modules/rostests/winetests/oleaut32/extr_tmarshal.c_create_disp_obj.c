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
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct disp_obj {int ref; TYPE_1__ ISomethingFromDispatch_iface; } ;
typedef  TYPE_1__ ISomethingFromDispatch ;

/* Variables and functions */
 struct disp_obj* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  disp_obj_vtbl ; 

__attribute__((used)) static ISomethingFromDispatch *create_disp_obj(void)
{
    struct disp_obj *obj = CoTaskMemAlloc(sizeof(*obj));
    obj->ISomethingFromDispatch_iface.lpVtbl = &disp_obj_vtbl;
    obj->ref = 1;
    return &obj->ISomethingFromDispatch_iface;
}