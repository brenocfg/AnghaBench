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
struct paste_buffer {size_t size; char const* data; } ;

/* Variables and functions */

const char *
paste_buffer_data(struct paste_buffer *pb, size_t *size)
{
	if (size != NULL)
		*size = pb->size;
	return (pb->data);
}