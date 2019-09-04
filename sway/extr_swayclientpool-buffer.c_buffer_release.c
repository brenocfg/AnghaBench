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
struct wl_buffer {int dummy; } ;
struct pool_buffer {int busy; } ;

/* Variables and functions */

__attribute__((used)) static void buffer_release(void *data, struct wl_buffer *wl_buffer) {
	struct pool_buffer *buffer = data;
	buffer->busy = false;
}