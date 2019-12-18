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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_pointer {int dummy; } ;
struct seat_data {int /*<<< orphan*/  cursor_serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  pointer_show (struct seat_data*,struct wl_pointer*) ; 

__attribute__((used)) static void pointer_enter_cb(void *data, struct wl_pointer *pointer,
                             uint32_t serial, struct wl_surface *surface,
                             wl_fixed_t sx, wl_fixed_t sy)
{
    struct seat_data *sd = data;

    sd->cursor_serial = serial;
    pointer_show(sd, pointer);
    (void) surface; (void) sx; (void) sy;
}