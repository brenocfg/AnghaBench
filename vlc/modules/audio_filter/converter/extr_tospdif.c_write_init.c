#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_8__ {size_t i_out_offset; TYPE_6__* p_out_buf; } ;
typedef  TYPE_2__ filter_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_10__ {unsigned int i_nb_samples; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;

/* Variables and functions */
 size_t SPDIF_HEADER_SIZE ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__* block_Alloc (size_t) ; 

__attribute__((used)) static int write_init( filter_t *p_filter, block_t *p_in_buf,
                       size_t i_out_size, unsigned i_nb_samples )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    assert( p_sys->p_out_buf == NULL );
    assert( i_out_size > SPDIF_HEADER_SIZE && ( i_out_size & 3 ) == 0 );

    p_sys->p_out_buf = block_Alloc( i_out_size );
    if( !p_sys->p_out_buf )
        return VLC_ENOMEM;
    p_sys->p_out_buf->i_dts = p_in_buf->i_dts;
    p_sys->p_out_buf->i_pts = p_in_buf->i_pts;
    p_sys->p_out_buf->i_nb_samples = i_nb_samples;

    p_sys->i_out_offset = SPDIF_HEADER_SIZE; /* Place for the S/PDIF header */
    return VLC_SUCCESS;
}