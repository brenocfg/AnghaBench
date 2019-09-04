#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  entry; void* value; void* name; } ;
typedef  TYPE_1__ param_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  props; } ;
typedef  TYPE_2__ PropertyBag ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free_prop (TYPE_1__*) ; 
 TYPE_1__* heap_alloc (int) ; 
 void* heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT add_prop(PropertyBag *prop_bag, const WCHAR *name, const WCHAR *value)
{
    param_prop_t *prop;

    if(!name || !value)
        return S_OK;

    TRACE("%p %s %s\n", prop_bag, debugstr_w(name), debugstr_w(value));

    prop = heap_alloc(sizeof(*prop));
    if(!prop)
        return E_OUTOFMEMORY;

    prop->name = heap_strdupW(name);
    prop->value = heap_strdupW(value);
    if(!prop->name || !prop->value) {
        list_init(&prop->entry);
        free_prop(prop);
        return E_OUTOFMEMORY;
    }

    list_add_tail(&prop_bag->props, &prop->entry);
    return S_OK;
}