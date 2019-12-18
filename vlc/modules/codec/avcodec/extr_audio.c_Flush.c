#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {int i_reject_count; int /*<<< orphan*/  end_date; TYPE_3__* p_context; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_9__ {scalar_t__ codec_id; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MP2 ; 
 scalar_t__ AV_CODEC_ID_MP3 ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  avcodec_flush_buffers (TYPE_3__*) ; 
 scalar_t__ avcodec_is_open (TYPE_3__*) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Flush( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    AVCodecContext *ctx = p_sys->p_context;

    if( avcodec_is_open( ctx ) )
        avcodec_flush_buffers( ctx );
    date_Set( &p_sys->end_date, VLC_TICK_INVALID );

    if( ctx->codec_id == AV_CODEC_ID_MP2 ||
        ctx->codec_id == AV_CODEC_ID_MP3 )
        p_sys->i_reject_count = 3;
}