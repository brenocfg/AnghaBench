#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int has_double_click; } ;
struct TYPE_12__ {int /*<<< orphan*/  owner; int /*<<< orphan*/ * sys; TYPE_1__ info; int /*<<< orphan*/  handle; } ;
struct TYPE_11__ {int inhibit_windowed; int active; int fullscreen; int /*<<< orphan*/  lock; int /*<<< orphan*/ * inhibit; int /*<<< orphan*/  module; TYPE_3__ wnd; } ;
typedef  TYPE_2__ window_t ;
typedef  TYPE_3__ vout_window_t ;
typedef  int /*<<< orphan*/  vout_window_owner_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_inhibit_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * vlc_inhibit_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_module_load (TYPE_3__*,char*,char const*,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_3__*) ; 
 int /*<<< orphan*/  vout_window_start ; 

vout_window_t *vout_window_New(vlc_object_t *obj, const char *module,
                               const vout_window_owner_t *owner)
{
    window_t *w = vlc_custom_create(obj, sizeof(*w), "window");
    vout_window_t *window = &w->wnd;

    memset(&window->handle, 0, sizeof(window->handle));
    window->info.has_double_click = false;
    window->sys = NULL;
    assert(owner != NULL);
    window->owner = *owner;

    int dss = var_InheritInteger(obj, "disable-screensaver");

    w->inhibit = NULL;
    w->inhibit_windowed = dss == 1;
    w->active = false;
    w->fullscreen = false;
    vlc_mutex_init(&w->lock);

    w->module = vlc_module_load(window, "vout window", module, false,
                                vout_window_start, window);
    if (!w->module) {
        vlc_mutex_destroy(&w->lock);
        vlc_object_delete(window);
        return NULL;
    }

    /* Hook for screensaver inhibition */
    if (dss > 0) {
        vlc_inhibit_t *inh = vlc_inhibit_Create(VLC_OBJECT(window));

        vlc_mutex_lock(&w->lock);
        w->inhibit = inh;
        vlc_mutex_unlock(&w->lock);
    }
    return window;
}