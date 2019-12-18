#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sout_mux_t ;
typedef  int /*<<< orphan*/  sout_input_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int AddStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    VLC_UNUSED(p_input);
    msg_Dbg( p_mux, "adding input" );
    return VLC_SUCCESS;
}