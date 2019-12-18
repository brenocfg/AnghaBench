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
struct TYPE_3__ {int /*<<< orphan*/ * p_begin; int /*<<< orphan*/ * p_memory; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int BufferDestroy( buffer_t *p_buffer )
{
    free( p_buffer->p_memory );
    p_buffer->p_memory = NULL;
    p_buffer->p_begin = NULL;

    return VLC_SUCCESS;
}