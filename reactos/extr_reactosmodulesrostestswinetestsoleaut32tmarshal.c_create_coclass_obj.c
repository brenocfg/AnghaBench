#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct coclass_obj {int ref; TYPE_2__ ICoclass2_iface; TYPE_1__ ICoclass1_iface; } ;

/* Variables and functions */
 struct coclass_obj* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  coclass1_vtbl ; 
 int /*<<< orphan*/  coclass2_vtbl ; 

__attribute__((used)) static struct coclass_obj *create_coclass_obj(void)
{
    struct coclass_obj *obj = CoTaskMemAlloc(sizeof(*obj));
    obj->ICoclass1_iface.lpVtbl = &coclass1_vtbl;
    obj->ICoclass2_iface.lpVtbl = &coclass2_vtbl;
    obj->ref = 1;
    return obj;
}