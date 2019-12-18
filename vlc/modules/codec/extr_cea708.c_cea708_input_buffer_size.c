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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  capacity; } ;
typedef  TYPE_1__ cea708_input_buffer_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t cea708_input_buffer_size(const cea708_input_buffer_t *ib)
{
    return ib->capacity;
}