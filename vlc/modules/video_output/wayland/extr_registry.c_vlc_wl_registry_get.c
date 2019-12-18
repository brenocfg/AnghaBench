#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wl_proxy {int dummy; } ;
struct wl_event_queue {int dummy; } ;
struct wl_display {int dummy; } ;
struct vlc_wl_registry {int /*<<< orphan*/ * registry; int /*<<< orphan*/ * names; int /*<<< orphan*/ * interfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_wl_registry*) ; 
 struct vlc_wl_registry* malloc (int) ; 
 int /*<<< orphan*/  registry_cbs ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_wl_registry_destroy (struct vlc_wl_registry*) ; 
 int /*<<< orphan*/ * wl_display_get_registry (struct wl_display*) ; 
 scalar_t__ wl_display_roundtrip_queue (struct wl_display*,struct wl_event_queue*) ; 
 struct wl_display* wl_proxy_create_wrapper (struct wl_display*) ; 
 int /*<<< orphan*/  wl_proxy_set_queue (struct wl_proxy*,struct wl_event_queue*) ; 
 int /*<<< orphan*/  wl_proxy_wrapper_destroy (struct wl_display*) ; 
 int /*<<< orphan*/  wl_registry_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vlc_wl_registry*) ; 

struct vlc_wl_registry *vlc_wl_registry_get(struct wl_display *display,
                                            struct wl_event_queue *queue)
{
    struct vlc_wl_registry *vr = malloc(sizeof (*vr));
    if (unlikely(vr == NULL))
        return NULL;

    struct wl_display *wrapper = wl_proxy_create_wrapper(display);
    if (unlikely(wrapper == NULL))
        goto error;

    wl_proxy_set_queue((struct wl_proxy *)wrapper, queue);
    vr->registry = wl_display_get_registry(wrapper);
    wl_proxy_wrapper_destroy(wrapper);

    if (unlikely(vr->registry == NULL))
        goto error;

    vr->interfaces = NULL;
    vr->names = NULL;

    wl_registry_add_listener(vr->registry, &registry_cbs, vr);

     /* complete registry enumeration */
    if (wl_display_roundtrip_queue(display, queue) < 0)
    {
        vlc_wl_registry_destroy(vr);
        vr = NULL;
    }

    return vr;
error:
    free(vr);
    return vr;
}