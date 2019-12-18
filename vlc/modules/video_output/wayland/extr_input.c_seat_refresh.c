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
typedef  scalar_t__ vlc_tick_t ;
struct seat_data {scalar_t__ cursor_deadline; int /*<<< orphan*/  cursor_serial; int /*<<< orphan*/ * pointer; } ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seat_refresh(struct seat_data *sd, vlc_tick_t now)
{
    if (sd->pointer != NULL && sd->cursor_deadline <= now)
    {   /* Hide cursor */
        wl_pointer_set_cursor(sd->pointer, sd->cursor_serial, NULL, 0, 0);
        sd->cursor_deadline = INT64_MAX;
    }
}