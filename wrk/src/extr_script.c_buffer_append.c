#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t cursor; size_t buffer; size_t length; } ;
typedef  TYPE_1__ buffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,char const*,size_t) ; 
 size_t realloc (size_t,int) ; 

void buffer_append(buffer *b, const char *data, size_t len) {
    size_t used = b->cursor - b->buffer;
    while (used + len + 1 >= b->length) {
        b->length += 1024;
        b->buffer  = realloc(b->buffer, b->length);
        b->cursor  = b->buffer + used;
    }
    memcpy(b->cursor, data, len);
    b->cursor += len;
}