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
struct wined3d_string_buffer {int buffer_size; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  heap_alloc (int) ; 
 int /*<<< orphan*/  string_buffer_clear (struct wined3d_string_buffer*) ; 

BOOL string_buffer_init(struct wined3d_string_buffer *buffer)
{
    buffer->buffer_size = 32;
    if (!(buffer->buffer = heap_alloc(buffer->buffer_size)))
    {
        ERR("Failed to allocate shader buffer memory.\n");
        return FALSE;
    }

    string_buffer_clear(buffer);
    return TRUE;
}