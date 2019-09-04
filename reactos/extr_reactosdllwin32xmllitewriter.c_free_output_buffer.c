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
struct output_buffer {scalar_t__ written; scalar_t__ allocated; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {struct output_buffer buffer; } ;
typedef  TYPE_1__ xmlwriteroutput ;

/* Variables and functions */
 int /*<<< orphan*/  writeroutput_free (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_output_buffer(xmlwriteroutput *output)
{
    struct output_buffer *buffer = &output->buffer;
    writeroutput_free(output, buffer->data);
    buffer->data = NULL;
    buffer->allocated = 0;
    buffer->written = 0;
}