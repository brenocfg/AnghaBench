#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_8__ {TYPE_1__* vtbl; } ;
struct TYPE_7__ {TYPE_3__ node; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* invoke ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  TYPE_2__ HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  int /*<<< orphan*/  DispatchEx ;
typedef  int /*<<< orphan*/  DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 TYPE_2__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLElement_invoke(DispatchEx *dispex, DISPID id, LCID lcid,
        WORD flags, DISPPARAMS *params, VARIANT *res, EXCEPINFO *ei,
        IServiceProvider *caller)
{
    HTMLElement *This = impl_from_DispatchEx(dispex);

    if(This->node.vtbl->invoke)
        return This->node.vtbl->invoke(&This->node, id, lcid, flags,
                params, res, ei, caller);

    ERR("(%p): element has no invoke method\n", This);
    return E_NOTIMPL;
}