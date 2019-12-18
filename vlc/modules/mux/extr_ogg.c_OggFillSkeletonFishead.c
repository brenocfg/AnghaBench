#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_5__ {int i_pos; int i_segment_start; int i_data_start; } ;
typedef  TYPE_2__ sout_mux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetQWLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetWLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void OggFillSkeletonFishead( uint8_t *p_buffer, sout_mux_t *p_mux )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    memcpy( p_buffer, "fishead", 8 );
    SetWLE( &p_buffer[8], 4 );
    SetWLE( &p_buffer[10], 0 );
    SetQWLE( &p_buffer[20], 1000 );
    SetQWLE( &p_buffer[36], 1000 );
    SetQWLE( &p_buffer[64], p_sys->i_pos - p_sys->i_segment_start ); /* segment length */
    SetQWLE( &p_buffer[72], p_sys->i_data_start - p_sys->i_segment_start ); /* data start offset */
}