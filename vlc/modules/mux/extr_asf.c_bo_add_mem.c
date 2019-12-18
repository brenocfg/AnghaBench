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
struct TYPE_3__ {size_t i_buffer; int /*<<< orphan*/ * p_buffer; scalar_t__ i_buffer_size; } ;
typedef  TYPE_1__ bo_t ;

/* Variables and functions */
 int __MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bo_add_mem( bo_t *p_bo, uint8_t *p_mem, int i_size )
{
    int i_copy = __MIN( i_size, p_bo->i_buffer_size - p_bo->i_buffer );

    if( i_copy > 0 )
    {
        memcpy( &p_bo->p_buffer[p_bo->i_buffer], p_mem, i_copy );
    }
    p_bo->i_buffer += i_size;
}