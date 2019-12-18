#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_7__ {TYPE_3__* p_mux; int /*<<< orphan*/ * p_session; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
typedef  int /*<<< orphan*/  sout_access_out_t ;
struct TYPE_8__ {int /*<<< orphan*/ * p_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sout_AccessOutDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_AnnounceUnRegister (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sout_MuxDelete (TYPE_3__*) ; 

__attribute__((used)) static void Close( vlc_object_t * p_this )
{
    sout_stream_t     *p_stream = (sout_stream_t*)p_this;
    sout_stream_sys_t *p_sys    = p_stream->p_sys;
    sout_access_out_t *p_access = p_sys->p_mux->p_access;

    if( p_sys->p_session != NULL )
        sout_AnnounceUnRegister( p_stream, p_sys->p_session );

    sout_MuxDelete( p_sys->p_mux );
    sout_AccessOutDelete( p_access );

    free( p_sys );
}