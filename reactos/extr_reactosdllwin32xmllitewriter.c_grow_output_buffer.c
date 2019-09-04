#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct output_buffer {int allocated; int written; char* data; } ;
struct TYPE_4__ {struct output_buffer buffer; } ;
typedef  TYPE_1__ xmlwriteroutput ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int max (int,int) ; 
 char* writeroutput_realloc (TYPE_1__*,char*,int) ; 

__attribute__((used)) static HRESULT grow_output_buffer(xmlwriteroutput *output, int length)
{
    struct output_buffer *buffer = &output->buffer;
    /* grow if needed, plus 4 bytes to be sure null terminator will fit in */
    if (buffer->allocated < buffer->written + length + 4) {
        int grown_size = max(2*buffer->allocated, buffer->allocated + length);
        char *ptr = writeroutput_realloc(output, buffer->data, grown_size);
        if (!ptr) return E_OUTOFMEMORY;
        buffer->data = ptr;
        buffer->allocated = grown_size;
    }

    return S_OK;
}