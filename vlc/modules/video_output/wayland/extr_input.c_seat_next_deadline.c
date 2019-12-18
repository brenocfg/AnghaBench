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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct seat_data {int /*<<< orphan*/  cursor_deadline; int /*<<< orphan*/ * pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 

__attribute__((used)) static vlc_tick_t seat_next_deadline(const struct seat_data *sd)
{
    return (sd->pointer != NULL) ? sd->cursor_deadline : INT64_MAX;
}