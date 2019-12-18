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
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_af_chain; int /*<<< orphan*/  decoder_out; int /*<<< orphan*/  encoder; } ;
typedef  TYPE_1__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_FiltersDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transcode_encoder_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcode_encoder_delete (int /*<<< orphan*/ ) ; 

void transcode_audio_clean( sout_stream_t *p_stream, sout_stream_id_sys_t *id )
{
    /* Close encoder */
    transcode_encoder_close( id->encoder );
    transcode_encoder_delete( id->encoder );

    es_format_Clean( &id->decoder_out );

    /* Close filters */
    if( id->p_af_chain != NULL )
        aout_FiltersDelete( p_stream, id->p_af_chain );
}