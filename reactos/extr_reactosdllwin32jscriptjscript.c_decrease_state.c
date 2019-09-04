#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* name; int /*<<< orphan*/ * disp; struct TYPE_9__* next; } ;
typedef  TYPE_2__ named_item_t ;
struct TYPE_10__ {int /*<<< orphan*/ * site; scalar_t__ thread_id; TYPE_1__* ctx; } ;
struct TYPE_8__ {int state; int /*<<< orphan*/ * global; int /*<<< orphan*/ * site; int /*<<< orphan*/ * secmgr; TYPE_2__* named_items; int /*<<< orphan*/ * host_global; } ;
typedef  int SCRIPTSTATE ;
typedef  TYPE_3__ JScript ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IActiveScriptSite_OnStateChange (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IActiveScriptSite_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IInternetHostSecurityManager_Release (int /*<<< orphan*/ *) ; 
#define  SCRIPTSTATE_CONNECTED 132 
#define  SCRIPTSTATE_DISCONNECTED 131 
#define  SCRIPTSTATE_INITIALIZED 130 
#define  SCRIPTSTATE_STARTED 129 
#define  SCRIPTSTATE_UNINITIALIZED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_state (TYPE_3__*,int) ; 
 int /*<<< orphan*/  clear_script_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decrease_state(JScript *This, SCRIPTSTATE state)
{
    if(This->ctx) {
        switch(This->ctx->state) {
        case SCRIPTSTATE_CONNECTED:
            change_state(This, SCRIPTSTATE_DISCONNECTED);
            if(state == SCRIPTSTATE_DISCONNECTED)
                return;
            /* FALLTHROUGH */
        case SCRIPTSTATE_STARTED:
        case SCRIPTSTATE_DISCONNECTED:
            clear_script_queue(This);

            if(This->ctx->state == SCRIPTSTATE_DISCONNECTED)
                change_state(This, SCRIPTSTATE_INITIALIZED);
            if(state == SCRIPTSTATE_INITIALIZED)
                return;
            /* FALLTHROUGH */
        case SCRIPTSTATE_INITIALIZED:
            if(This->ctx->host_global) {
                IDispatch_Release(This->ctx->host_global);
                This->ctx->host_global = NULL;
            }

            if(This->ctx->named_items) {
                named_item_t *iter, *iter2;

                iter = This->ctx->named_items;
                while(iter) {
                    iter2 = iter->next;

                    if(iter->disp)
                        IDispatch_Release(iter->disp);
                    heap_free(iter->name);
                    heap_free(iter);
                    iter = iter2;
                }

                This->ctx->named_items = NULL;
            }

            if(This->ctx->secmgr) {
                IInternetHostSecurityManager_Release(This->ctx->secmgr);
                This->ctx->secmgr = NULL;
            }

            if(This->ctx->site) {
                IActiveScriptSite_Release(This->ctx->site);
                This->ctx->site = NULL;
            }

            if(This->ctx->global) {
                jsdisp_release(This->ctx->global);
                This->ctx->global = NULL;
            }
            /* FALLTHROUGH */
        case SCRIPTSTATE_UNINITIALIZED:
            change_state(This, state);
            break;
        default:
            assert(0);
        }

        change_state(This, state);
    }else if(state == SCRIPTSTATE_UNINITIALIZED) {
        if(This->site)
            IActiveScriptSite_OnStateChange(This->site, state);
    }else {
        FIXME("NULL ctx\n");
    }

    if(state == SCRIPTSTATE_UNINITIALIZED)
        This->thread_id = 0;

    if(This->site) {
        IActiveScriptSite_Release(This->site);
        This->site = NULL;
    }
}