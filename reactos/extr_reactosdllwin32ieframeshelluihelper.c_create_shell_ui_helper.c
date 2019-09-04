#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IShellUIHelper2_iface; } ;
typedef  TYPE_1__ ShellUIHelper ;
typedef  TYPE_2__ IShellUIHelper2 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ShellUIHelper2Vtbl ; 
 TYPE_1__* heap_alloc (int) ; 

HRESULT create_shell_ui_helper(IShellUIHelper2 **_ret)
{
    ShellUIHelper *ret;

    ret = heap_alloc(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IShellUIHelper2_iface.lpVtbl = &ShellUIHelper2Vtbl;
    ret->ref = 1;

    *_ret = &ret->IShellUIHelper2_iface;
    return S_OK;
}