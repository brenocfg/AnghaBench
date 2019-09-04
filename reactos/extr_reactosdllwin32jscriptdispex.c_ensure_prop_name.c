#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_6__ {void* val; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_1__ u; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ dispex_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ PROP_DELETED ; 
 scalar_t__ PROP_JSVAL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* alloc_prop (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  find_prop_name_prot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__**) ; 
 void* jsval_undefined () ; 
 int /*<<< orphan*/  string_hash (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT ensure_prop_name(jsdisp_t *This, const WCHAR *name, DWORD create_flags, dispex_prop_t **ret)
{
    dispex_prop_t *prop;
    HRESULT hres;

    hres = find_prop_name_prot(This, string_hash(name), name, &prop);
    if(SUCCEEDED(hres) && (!prop || prop->type == PROP_DELETED)) {
        TRACE("creating prop %s flags %x\n", debugstr_w(name), create_flags);

        if(prop) {
            prop->type = PROP_JSVAL;
            prop->flags = create_flags;
            prop->u.val = jsval_undefined();
        }else {
            prop = alloc_prop(This, name, PROP_JSVAL, create_flags);
            if(!prop)
                return E_OUTOFMEMORY;
        }

        prop->u.val = jsval_undefined();
    }

    *ret = prop;
    return hres;
}