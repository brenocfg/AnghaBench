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
struct wl_pointer {int dummy; } ;
struct seat_data {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  pointer_show (struct seat_data*,struct wl_pointer*) ; 
 int /*<<< orphan*/  vout_window_ReportMouseMoved (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_fixed_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointer_motion_cb(void *data, struct wl_pointer *pointer,
                              uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
    struct seat_data *sd = data;

    pointer_show(sd, pointer);
    vout_window_ReportMouseMoved(sd->owner,
                                 wl_fixed_to_int(sx), wl_fixed_to_int(sy));
    (void) time;
}