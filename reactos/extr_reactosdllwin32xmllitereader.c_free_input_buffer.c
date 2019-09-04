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
struct TYPE_4__ {int /*<<< orphan*/  input; int /*<<< orphan*/  utf16; int /*<<< orphan*/  encoded; } ;
typedef  TYPE_1__ input_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  free_encoded_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerinput_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void free_input_buffer(input_buffer *buffer)
{
    free_encoded_buffer(buffer->input, &buffer->encoded);
    free_encoded_buffer(buffer->input, &buffer->utf16);
    readerinput_free(buffer->input, buffer);
}