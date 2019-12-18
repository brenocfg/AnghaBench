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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  capacity; int /*<<< orphan*/  start; int /*<<< orphan*/ * ringbuffer; } ;
typedef  TYPE_1__ cea708_input_buffer_t ;

/* Variables and functions */
 size_t CEA708_SERVICE_INPUT_BUFFER ; 
 scalar_t__ cea708_input_buffer_remain (TYPE_1__*) ; 

__attribute__((used)) static void cea708_input_buffer_add(cea708_input_buffer_t *ib, uint8_t a)
{
    if( cea708_input_buffer_remain(ib) > 0 )
        ib->ringbuffer[(ib->start + ib->capacity++) % CEA708_SERVICE_INPUT_BUFFER] = a;
}