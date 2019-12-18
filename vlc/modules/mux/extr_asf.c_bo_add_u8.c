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
struct TYPE_3__ {size_t i_buffer; size_t i_buffer_size; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_1__ bo_t ;

/* Variables and functions */

__attribute__((used)) static void bo_add_u8( bo_t *p_bo, uint8_t i )
{
    if( p_bo->i_buffer < p_bo->i_buffer_size )
    {
        p_bo->p_buffer[p_bo->i_buffer] = i;
    }
    p_bo->i_buffer++;
}