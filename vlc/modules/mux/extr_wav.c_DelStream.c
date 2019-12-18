#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_access; } ;
typedef  TYPE_1__ sout_mux_t ;
typedef  int /*<<< orphan*/  sout_input_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetHeader (TYPE_1__*) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 scalar_t__ sout_AccessOutSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DelStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    VLC_UNUSED(p_input);
    msg_Dbg( p_mux, "removing input" );

    msg_Dbg( p_mux, "writing header data" );
    if( sout_AccessOutSeek( p_mux->p_access, 0 ) == VLC_SUCCESS )
    {
        sout_AccessOutWrite( p_mux->p_access, GetHeader( p_mux ) );
    }
}