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
struct pool_buffer {int /*<<< orphan*/  size; scalar_t__ data; scalar_t__ pango; scalar_t__ surface; scalar_t__ cairo; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_destroy (scalar_t__) ; 
 int /*<<< orphan*/  cairo_surface_destroy (scalar_t__) ; 
 int /*<<< orphan*/  g_object_unref (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct pool_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_buffer_destroy (scalar_t__) ; 

void destroy_buffer(struct pool_buffer *buffer) {
	if (buffer->buffer) {
		wl_buffer_destroy(buffer->buffer);
	}
	if (buffer->cairo) {
		cairo_destroy(buffer->cairo);
	}
	if (buffer->surface) {
		cairo_surface_destroy(buffer->surface);
	}
	if (buffer->pango) {
		g_object_unref(buffer->pango);
	}
	if (buffer->data) {
		munmap(buffer->data, buffer->size);
	}
	memset(buffer, 0, sizeof(struct pool_buffer));
}