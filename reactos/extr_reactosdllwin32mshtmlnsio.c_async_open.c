#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  header; TYPE_6__* bscallback; TYPE_3__* window; } ;
typedef  TYPE_5__ start_binding_task_t ;
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIStreamListener ;
struct TYPE_20__ {int /*<<< orphan*/  IBindStatusCallback_iface; } ;
struct TYPE_24__ {TYPE_2__ bsc; } ;
typedef  TYPE_6__ nsChannelBSC ;
struct TYPE_25__ {TYPE_1__* uri; } ;
typedef  TYPE_7__ nsChannel ;
struct TYPE_22__ {TYPE_3__* inner_window; } ;
struct TYPE_26__ {TYPE_4__ base; int /*<<< orphan*/  pending_window; } ;
struct TYPE_21__ {int /*<<< orphan*/  task_magic; } ;
struct TYPE_19__ {int /*<<< orphan*/  uri; } ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  TYPE_8__ HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BINDING_NAVIGATED ; 
 int /*<<< orphan*/  CreateURLMonikerEx2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NS_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  NS_ERROR_UNEXPECTED ; 
 int /*<<< orphan*/  NS_OK ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_start_doc_binding (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channelbsc_set_channel (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_channelbsc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  create_pending_window (TYPE_8__*,TYPE_6__*) ; 
 TYPE_5__* heap_alloc (int) ; 
 int /*<<< orphan*/  push_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_mon (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_binding_proc ; 
 int /*<<< orphan*/  start_binding_task_destr ; 

__attribute__((used)) static nsresult async_open(nsChannel *This, HTMLOuterWindow *window, BOOL is_doc_channel, nsIStreamListener *listener,
        nsISupports *context)
{
    nsChannelBSC *bscallback;
    IMoniker *mon = NULL;
    HRESULT hres;

    hres = CreateURLMonikerEx2(NULL, This->uri->uri, &mon, 0);
    if(FAILED(hres)) {
        WARN("CreateURLMoniker failed: %08x\n", hres);
        return NS_ERROR_UNEXPECTED;
    }

    if(is_doc_channel)
        set_current_mon(window, mon, BINDING_NAVIGATED);

    hres = create_channelbsc(mon, NULL, NULL, 0, is_doc_channel, &bscallback);
    IMoniker_Release(mon);
    if(FAILED(hres))
        return NS_ERROR_UNEXPECTED;

    channelbsc_set_channel(bscallback, This, listener, context);

    if(is_doc_channel) {
        hres = create_pending_window(window, bscallback);
        if(SUCCEEDED(hres))
            async_start_doc_binding(window, window->pending_window);
        IBindStatusCallback_Release(&bscallback->bsc.IBindStatusCallback_iface);
        if(FAILED(hres))
            return NS_ERROR_UNEXPECTED;
    }else {
        start_binding_task_t *task;

        task = heap_alloc(sizeof(start_binding_task_t));
        if(!task) {
            IBindStatusCallback_Release(&bscallback->bsc.IBindStatusCallback_iface);
            return NS_ERROR_OUT_OF_MEMORY;
        }

        task->window = window->base.inner_window;
        task->bscallback = bscallback;
        hres = push_task(&task->header, start_binding_proc, start_binding_task_destr, window->base.inner_window->task_magic);
        if(FAILED(hres))
            return NS_ERROR_OUT_OF_MEMORY;
    }

    return NS_OK;
}