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
struct wl_display {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl_display_cancel_read (struct wl_display*) ; 

__attribute__((used)) static void cleanup_wl_display_read(void *data)
{
    struct wl_display *display = data;

    wl_display_cancel_read(display);
}