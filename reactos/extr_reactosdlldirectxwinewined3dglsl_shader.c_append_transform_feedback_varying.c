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
struct wined3d_string_buffer {scalar_t__ content_size; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void append_transform_feedback_varying(const char **varyings, unsigned int *varying_count,
        char **strings, unsigned int *strings_length, struct wined3d_string_buffer *buffer)
{
    if (varyings && *strings)
    {
        char *ptr = *strings;

        varyings[*varying_count] = ptr;

        memcpy(ptr, buffer->buffer, buffer->content_size + 1);
        ptr += buffer->content_size + 1;

        *strings = ptr;
    }

    *strings_length += buffer->content_size + 1;
    ++(*varying_count);
}