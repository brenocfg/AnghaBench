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
typedef  int uint8_t ;
struct TYPE_3__ {int capacity; int start; int* ringbuffer; } ;
typedef  TYPE_1__ cea708_input_buffer_t ;

/* Variables and functions */
 int CEA708_SERVICE_INPUT_BUFFER ; 

__attribute__((used)) static uint8_t cea708_input_buffer_peek(cea708_input_buffer_t *ib, uint8_t off)
{
    if(off + 1 > ib->capacity)
        return 0;
    off = (ib->start + off) % CEA708_SERVICE_INPUT_BUFFER;
    return ib->ringbuffer[off];
}