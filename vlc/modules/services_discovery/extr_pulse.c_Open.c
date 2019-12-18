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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int /*<<< orphan*/  description; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_8__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/ * root; int /*<<< orphan*/ * context; } ;
typedef  TYPE_2__ services_discovery_sys_t ;
typedef  int /*<<< orphan*/  pa_subscription_mask_t ;
typedef  int /*<<< orphan*/  pa_operation ;
typedef  int /*<<< orphan*/  pa_context ;

/* Variables and functions */
 int /*<<< orphan*/  ContextCallback ; 
 int /*<<< orphan*/  PA_SUBSCRIPTION_MASK_SOURCE ; 
 int /*<<< orphan*/  SourceCallback ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/ * pa_context_get_source_info_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pa_context_set_subscribe_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * pa_context_subscribe (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_pa_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    services_discovery_t *sd = (services_discovery_t *)obj;
    pa_operation *op;
    pa_context *ctx;

    services_discovery_sys_t *sys = malloc (sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    ctx = vlc_pa_connect (obj, &sys->mainloop);
    if (ctx == NULL)
    {
        free (sys);
        return VLC_EGENERIC;
    }

    sd->p_sys = sys;
    sd->description = _("Audio capture");
    sys->context = ctx;
    sys->root = NULL;

    /* Subscribe for source events */
    const pa_subscription_mask_t mask = PA_SUBSCRIPTION_MASK_SOURCE;
    pa_threaded_mainloop_lock (sys->mainloop);
    pa_context_set_subscribe_callback (ctx, ContextCallback, sd);
    op = pa_context_subscribe (ctx, mask, NULL, NULL);
    if (likely(op != NULL))
        pa_operation_unref (op);

    /* Enumerate existing sources */
    op = pa_context_get_source_info_list (ctx, SourceCallback, sd);
    if (likely(op != NULL))
    {
        //while (pa_operation_get_state (op) == PA_OPERATION_RUNNING)
        //    pa_threaded_mainloop_wait (sys->mainloop);
        pa_operation_unref (op);
    }
    pa_threaded_mainloop_unlock (sys->mainloop);
    return VLC_SUCCESS;
/*
error:
    pa_threaded_mainloop_unlock (sys->mainloop);
    vlc_pa_disconnect (obj, ctx, sys->mainloop);
    free (sys);
    return VLC_EGENERIC;*/
}