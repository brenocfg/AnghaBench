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
struct buffer_data {int /*<<< orphan*/ * counter; int /*<<< orphan*/  picture; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct buffer_data*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_buffer_destroy (struct wl_buffer*) ; 

__attribute__((used)) static void buffer_release_cb(void *data, struct wl_buffer *buffer)
{
    struct buffer_data *d = data;

    picture_Release(d->picture);
    (*(d->counter))--;
    free(d);
    wl_buffer_destroy(buffer);
}