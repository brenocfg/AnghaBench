#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int b_flushed; int /*<<< orphan*/ * id; TYPE_2__* p_sout; } ;
typedef  TYPE_1__ sout_packetizer_input_t ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_stream; } ;
typedef  TYPE_2__ sout_instance_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_3__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,char*,void*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,void*) ; 
 int /*<<< orphan*/ * sout_StreamIdAdd (int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

sout_packetizer_input_t *sout_InputNew( sout_instance_t *p_sout,
                                        const es_format_t *p_fmt )
{
    sout_packetizer_input_t *p_input;

    /* *** create a packetizer input *** */
    if( !p_fmt->i_codec || !(p_input = malloc(sizeof(sout_packetizer_input_t))) )
        return NULL;

    p_input->p_sout = p_sout;
    p_input->b_flushed = false;

    msg_Dbg( p_sout, "adding a new sout input for `%4.4s` (sout_input: %p)",
             (char*) &p_fmt->i_codec, (void *)p_input );

    /* *** add it to the stream chain */
    vlc_mutex_lock( &p_sout->lock );
    p_input->id = sout_StreamIdAdd( p_sout->p_stream, p_fmt );
    vlc_mutex_unlock( &p_sout->lock );

    if( p_input->id == NULL )
    {
        msg_Warn( p_sout, "new sout input failed (sout_input: %p)",
                 (void *)p_input );
        free( p_input );
        p_input = NULL;
    }

    return( p_input );
}