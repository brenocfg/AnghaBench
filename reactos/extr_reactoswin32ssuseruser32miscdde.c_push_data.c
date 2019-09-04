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
struct packed_message {int size; int /*<<< orphan*/  count; void const* data; } ;

/* Variables and functions */

__attribute__((used)) static inline void push_data( struct packed_message *data, const void *ptr, int size )
{
    data->data = ptr;
    data->size = size;
    data->count++;
}