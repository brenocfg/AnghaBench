#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* content_window; } ;
struct TYPE_9__ {TYPE_3__ framebase; } ;
struct TYPE_6__ {int /*<<< orphan*/  inner_window; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
typedef  TYPE_4__ HTMLFrameElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 TYPE_4__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_window_props (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLFrameElement_get_dispid(HTMLDOMNode *iface, BSTR name,
        DWORD grfdex, DISPID *pid)
{
    HTMLFrameElement *This = impl_from_HTMLDOMNode(iface);

    if(!This->framebase.content_window)
        return DISP_E_UNKNOWNNAME;

    return search_window_props(This->framebase.content_window->base.inner_window, name, grfdex, pid);
}