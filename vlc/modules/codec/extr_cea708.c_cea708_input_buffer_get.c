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
struct TYPE_4__ {int start; int /*<<< orphan*/  capacity; } ;
typedef  TYPE_1__ cea708_input_buffer_t ;

/* Variables and functions */
 int CEA708_SERVICE_INPUT_BUFFER ; 
 int /*<<< orphan*/  cea708_input_buffer_peek (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t cea708_input_buffer_get(cea708_input_buffer_t *ib)
{
    uint8_t a = cea708_input_buffer_peek( ib, 0 );
    ib->start = (ib->start + 1) % CEA708_SERVICE_INPUT_BUFFER;
    ib->capacity--;
    return a;
}