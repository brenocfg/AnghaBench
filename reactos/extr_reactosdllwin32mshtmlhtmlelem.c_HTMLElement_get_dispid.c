#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {TYPE_3__ node; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_dispid ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DispatchEx ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 TYPE_2__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLElement_get_dispid(DispatchEx *dispex, BSTR name,
        DWORD grfdex, DISPID *pid)
{
    HTMLElement *This = impl_from_DispatchEx(dispex);

    if(This->node.vtbl->get_dispid)
        return This->node.vtbl->get_dispid(&This->node, name, grfdex, pid);

    return DISP_E_UNKNOWNNAME;
}