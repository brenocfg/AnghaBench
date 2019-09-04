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
typedef  int /*<<< orphan*/  va_list ;
struct wined3d_string_buffer {unsigned int buffer_size; unsigned int content_size; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int vsnprintf (int /*<<< orphan*/ *,unsigned int,char const*,int /*<<< orphan*/ ) ; 

int shader_vaddline(struct wined3d_string_buffer *buffer, const char *format, va_list args)
{
    unsigned int rem;
    int rc;

    rem = buffer->buffer_size - buffer->content_size;
    rc = vsnprintf(&buffer->buffer[buffer->content_size], rem, format, args);
    if (rc < 0 /* C89 */ || (unsigned int)rc >= rem /* C99 */)
        return rc;

    buffer->content_size += rc;
    return 0;
}