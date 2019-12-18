#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_resource; int /*<<< orphan*/  b_video; int /*<<< orphan*/  b_audio; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_11__ {scalar_t__ i_cat; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_3__ es_format_t ;
typedef  void decoder_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 void* input_DecoderCreate (int /*<<< orphan*/ ,TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static void *Add( sout_stream_t *p_stream, const es_format_t *p_fmt )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;

    if( ( p_fmt->i_cat == AUDIO_ES && !p_sys->b_audio )||
        ( p_fmt->i_cat == VIDEO_ES && !p_sys->b_video ) )
    {
        return NULL;
    }

    decoder_t *p_dec = input_DecoderCreate( VLC_OBJECT(p_stream), p_fmt,
                                            p_sys->p_resource );
    if( p_dec == NULL )
    {
        msg_Err( p_stream, "cannot create decoder for fcc=`%4.4s'",
                 (char*)&p_fmt->i_codec );
        return NULL;
    }
    return p_dec;
}