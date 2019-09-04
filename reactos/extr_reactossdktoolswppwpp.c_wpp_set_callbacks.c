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
struct wpp_callbacks {int dummy; } ;

/* Variables and functions */
 struct wpp_callbacks const* wpp_callbacks ; 

void wpp_set_callbacks( const struct wpp_callbacks *callbacks )
{
    wpp_callbacks = callbacks;
}