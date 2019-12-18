#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * psz_text; } ;
typedef  TYPE_3__ webvtt_cue_t ;
struct callback_ctx {TYPE_1__* p_demux; } ;
struct TYPE_9__ {int i_count; int i_alloc; TYPE_3__* p_array; } ;
struct TYPE_11__ {TYPE_2__ cues; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;

/* Variables and functions */
 int SIZE_MAX ; 
 int WEBVTT_PREALLOC ; 
 TYPE_3__* realloc (TYPE_3__*,int) ; 

__attribute__((used)) static webvtt_cue_t * ParserGetCueHandler( void *priv )
{
    struct callback_ctx *ctx = (struct callback_ctx *) priv;
    demux_sys_t *p_sys = ctx->p_demux->p_sys;
    /* invalid recycled cue */
    if( p_sys->cues.i_count &&
        p_sys->cues.p_array[p_sys->cues.i_count - 1].psz_text == NULL )
    {
        return &p_sys->cues.p_array[p_sys->cues.i_count - 1];
    }

    if( p_sys->cues.i_alloc <= p_sys->cues.i_count &&
       (SIZE_MAX / sizeof(webvtt_cue_t)) - WEBVTT_PREALLOC > p_sys->cues.i_alloc )
    {
        webvtt_cue_t *p_realloc = realloc( p_sys->cues.p_array,
                sizeof(webvtt_cue_t) * ( p_sys->cues.i_alloc + WEBVTT_PREALLOC ) );
        if( p_realloc )
        {
            p_sys->cues.p_array = p_realloc;
            p_sys->cues.i_alloc += WEBVTT_PREALLOC;
        }
    }

    if( p_sys->cues.i_alloc > p_sys->cues.i_count )
        return &p_sys->cues.p_array[p_sys->cues.i_count++];

    return NULL;
}