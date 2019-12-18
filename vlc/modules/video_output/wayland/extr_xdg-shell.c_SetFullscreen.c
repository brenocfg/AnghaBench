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
struct TYPE_5__ {int /*<<< orphan*/  wl; } ;
struct TYPE_6__ {TYPE_1__ display; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_window_t ;
struct TYPE_7__ {unsigned long default_output; int /*<<< orphan*/  toplevel; int /*<<< orphan*/  registry; } ;
typedef  TYPE_3__ vout_window_sys_t ;
struct wl_output {int dummy; } ;

/* Variables and functions */
 unsigned long UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned long strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_output_destroy (struct wl_output*) ; 
 int /*<<< orphan*/  wl_output_interface ; 
 struct wl_output* wl_registry_bind (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xdg_toplevel_set_fullscreen (int /*<<< orphan*/ ,struct wl_output*) ; 

__attribute__((used)) static void SetFullscreen(vout_window_t *wnd, const char *idstr)
{
    vout_window_sys_t *sys = wnd->sys;
    struct wl_output *output = NULL;

    if (idstr != NULL)
    {
        char *end;
        unsigned long name = strtoul(idstr, &end, 10);

        assert(*end == '\0' && name <= UINT32_MAX);
        output = wl_registry_bind(sys->registry, name,
                                  &wl_output_interface, 1);
    }
    else
    if (sys->default_output != 0)
        output = wl_registry_bind(sys->registry, sys->default_output,
                                  &wl_output_interface, 1);

    xdg_toplevel_set_fullscreen(sys->toplevel, output);

    if (output != NULL)
        wl_output_destroy(output);

    wl_display_flush(wnd->display.wl);
}