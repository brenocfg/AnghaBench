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
struct TYPE_3__ {int options; } ;
typedef  TYPE_1__ mp4mux_handle_t ;
typedef  enum mp4mux_options { ____Placeholder_mp4mux_options } mp4mux_options ;

/* Variables and functions */

bool mp4mux_Is(mp4mux_handle_t *h, enum mp4mux_options o)
{
    return h->options & o;
}