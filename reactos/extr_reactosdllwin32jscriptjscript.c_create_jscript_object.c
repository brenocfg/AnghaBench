#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {int ref; TYPE_8__ IActiveScript_iface; int /*<<< orphan*/  is_encode; int /*<<< orphan*/  safeopt; TYPE_5__ IVariantChangeType_iface; TYPE_4__ IObjectSafety_iface; TYPE_3__ IActiveScriptProperty_iface; TYPE_2__ IActiveScriptParseProcedure2_iface; TYPE_1__ IActiveScriptParse_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_6__ JScript ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IActiveScript_QueryInterface (TYPE_8__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IActiveScript_Release (TYPE_8__*) ; 
 int /*<<< orphan*/  INTERFACE_USES_DISPEX ; 
 int /*<<< orphan*/  JScriptParseProcedureVtbl ; 
 int /*<<< orphan*/  JScriptParseVtbl ; 
 int /*<<< orphan*/  JScriptPropertyVtbl ; 
 int /*<<< orphan*/  JScriptSafetyVtbl ; 
 int /*<<< orphan*/  JScriptVtbl ; 
 int /*<<< orphan*/  VariantChangeTypeVtbl ; 
 TYPE_6__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  lock_module () ; 

HRESULT create_jscript_object(BOOL is_encode, REFIID riid, void **ppv)
{
    JScript *ret;
    HRESULT hres;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    lock_module();

    ret->IActiveScript_iface.lpVtbl = &JScriptVtbl;
    ret->IActiveScriptParse_iface.lpVtbl = &JScriptParseVtbl;
    ret->IActiveScriptParseProcedure2_iface.lpVtbl = &JScriptParseProcedureVtbl;
    ret->IActiveScriptProperty_iface.lpVtbl = &JScriptPropertyVtbl;
    ret->IObjectSafety_iface.lpVtbl = &JScriptSafetyVtbl;
    ret->IVariantChangeType_iface.lpVtbl = &VariantChangeTypeVtbl;
    ret->ref = 1;
    ret->safeopt = INTERFACE_USES_DISPEX;
    ret->is_encode = is_encode;

    hres = IActiveScript_QueryInterface(&ret->IActiveScript_iface, riid, ppv);
    IActiveScript_Release(&ret->IActiveScript_iface);
    return hres;
}