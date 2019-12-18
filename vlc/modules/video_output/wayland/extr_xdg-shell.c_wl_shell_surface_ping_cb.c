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
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_shell_surface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl_shell_surface_pong (struct wl_shell_surface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl_shell_surface_ping_cb(void *data,
                                     struct wl_shell_surface *surface,
                                     uint32_t serial)
{
    (void) data;
    wl_shell_surface_pong(surface, serial);
}