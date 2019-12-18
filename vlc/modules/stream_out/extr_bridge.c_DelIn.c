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
struct TYPE_6__ {int /*<<< orphan*/  p_next; scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;
struct TYPE_8__ {TYPE_2__* id_audio; TYPE_2__* id_video; } ;
typedef  TYPE_3__ in_sout_stream_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sout_StreamIdDel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DelIn( sout_stream_t *p_stream, void *_id )
{
    in_sout_stream_sys_t *p_sys = (in_sout_stream_sys_t *)p_stream->p_sys;
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;

    if( id == p_sys->id_video ) p_sys->id_video = NULL;
    if( id == p_sys->id_audio ) p_sys->id_audio = NULL;

    sout_StreamIdDel( p_stream->p_next, id->id );
    free( id );
}