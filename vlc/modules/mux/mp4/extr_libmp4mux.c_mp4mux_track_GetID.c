#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_track_id; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;

/* Variables and functions */

uint32_t mp4mux_track_GetID(const mp4mux_trackinfo_t *t)
{
    return t->i_track_id;
}