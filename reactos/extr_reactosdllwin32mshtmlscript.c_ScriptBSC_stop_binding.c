#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ readystate; int /*<<< orphan*/  IHTMLScriptElement_iface; } ;
struct TYPE_4__ {TYPE_2__* script_elem; scalar_t__ size; int /*<<< orphan*/ * buf; int /*<<< orphan*/  hres; } ;
typedef  TYPE_1__ ScriptBSC ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IHTMLScriptElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  READYSTATE_LOADED ; 
 scalar_t__ READYSTATE_LOADING ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_BSCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_script_elem_readystate (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT ScriptBSC_stop_binding(BSCallback *bsc, HRESULT result)
{
    ScriptBSC *This = impl_from_BSCallback(bsc);

    This->hres = result;

    if(SUCCEEDED(result)) {
        if(This->script_elem->readystate == READYSTATE_LOADING)
            set_script_elem_readystate(This->script_elem, READYSTATE_LOADED);
    }else {
        FIXME("binding failed %08x\n", result);
        heap_free(This->buf);
        This->buf = NULL;
        This->size = 0;
    }

    IHTMLScriptElement_Release(&This->script_elem->IHTMLScriptElement_iface);
    This->script_elem = NULL;
    return S_OK;
}