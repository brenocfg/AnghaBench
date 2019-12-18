#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_access; int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
typedef  int /*<<< orphan*/  sout_mux_sys_t ;
struct TYPE_7__ {int* p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 TYPE_2__* block_Alloc (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    sout_mux_t      *p_mux = (sout_mux_t*)p_this;
    sout_mux_sys_t  *p_sys = p_mux->p_sys;

    block_t   *p_end;

    msg_Info( p_mux, "Close" );

    p_end = block_Alloc( 4 );
    if( p_end )
    {
        p_end->p_buffer[0] = 0x00; p_end->p_buffer[1] = 0x00;
        p_end->p_buffer[2] = 0x01; p_end->p_buffer[3] = 0xb9;

        sout_AccessOutWrite( p_mux->p_access, p_end );
    }

    free( p_sys );
}