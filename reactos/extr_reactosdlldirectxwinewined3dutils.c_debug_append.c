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
struct debug_buffer {int size; int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * str; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int snprintf (int /*<<< orphan*/ *,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void debug_append(struct debug_buffer *buffer, const char *str, const char *separator)
{
    int size;

    if (!separator || buffer->ptr == buffer->str)
        separator = "";
    size = snprintf(buffer->ptr, buffer->size, "%s%s", separator, str);
    if (size == -1 || size >= buffer->size)
    {
        buffer->size = 0;
        strcpy(&buffer->str[ARRAY_SIZE(buffer->str) - 4], "...");
        return;
    }

    buffer->ptr += size;
    buffer->size -= size;
}