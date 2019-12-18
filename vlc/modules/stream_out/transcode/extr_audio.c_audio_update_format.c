#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct decoder_owner {TYPE_2__* id; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {TYPE_1__ fifo; int /*<<< orphan*/  decoder_out; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_format; } ;
struct TYPE_12__ {TYPE_7__ audio; int /*<<< orphan*/  i_codec; } ;
struct TYPE_11__ {TYPE_4__ fmt_out; } ;
typedef  TYPE_3__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_FMT_LINEAR (TYPE_7__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_7__*) ; 
 struct decoder_owner* dec_get_owner (TYPE_3__*) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_update_format( decoder_t *p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    sout_stream_id_sys_t *id = p_owner->id;

    p_dec->fmt_out.audio.i_format = p_dec->fmt_out.i_codec;
    aout_FormatPrepare( &p_dec->fmt_out.audio );

    if( !AOUT_FMT_LINEAR(&p_dec->fmt_out.audio) )
        return VLC_EGENERIC;

    vlc_mutex_lock(&id->fifo.lock);
    es_format_Clean( &id->decoder_out );
    es_format_Copy( &id->decoder_out, &p_dec->fmt_out );
    vlc_mutex_unlock(&id->fifo.lock);

    return VLC_SUCCESS;
}