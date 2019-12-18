#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ i_stop; scalar_t__ i_start; int /*<<< orphan*/ * psz_text; } ;
typedef  TYPE_5__ webvtt_cue_t ;
struct index_entry_s {int dummy; } ;
struct callback_ctx {int b_ordered; TYPE_1__* p_demux; } ;
struct TYPE_14__ {int i_alloc; int i_count; TYPE_9__* p_array; } ;
struct TYPE_13__ {int i_count; TYPE_2__* p_array; } ;
struct TYPE_16__ {scalar_t__ i_length; TYPE_4__ index; TYPE_3__ cues; } ;
typedef  TYPE_6__ demux_sys_t ;
struct TYPE_17__ {int active; scalar_t__ time; } ;
struct TYPE_12__ {scalar_t__ i_start; } ;
struct TYPE_11__ {TYPE_6__* p_sys; } ;

/* Variables and functions */
 int SIZE_MAX ; 
 int WEBVTT_PREALLOC ; 
 void* realloc (TYPE_9__*,int) ; 
 int /*<<< orphan*/  webvtt_cue_Clean (TYPE_5__*) ; 
 int /*<<< orphan*/  webvtt_cue_Init (TYPE_5__*) ; 

__attribute__((used)) static void ParserCueDoneHandler( void *priv, webvtt_cue_t *p_cue )
{
    struct callback_ctx *ctx = (struct callback_ctx *) priv;
    demux_sys_t *p_sys = ctx->p_demux->p_sys;
    if( p_cue->psz_text == NULL )
    {
        webvtt_cue_Clean( p_cue );
        webvtt_cue_Init( p_cue );
        return;
    }
    if( p_cue->i_stop > p_sys->i_length )
        p_sys->i_length = p_cue->i_stop;
    if( p_sys->cues.i_count > 0 &&
        p_sys->cues.p_array[p_sys->cues.i_count - 1].i_start != p_cue->i_start )
        ctx->b_ordered = false;

    /* Store timings */
    if( p_sys->index.i_alloc <= p_sys->index.i_count &&
       (SIZE_MAX / sizeof(struct index_entry_s)) - WEBVTT_PREALLOC * 2 > p_sys->index.i_alloc )
    {
        void *p_realloc = realloc( p_sys->index.p_array,
                                   sizeof(struct index_entry_s) *
                                   ( p_sys->index.i_alloc + WEBVTT_PREALLOC * 2 ) );
        if( p_realloc )
        {
            p_sys->index.p_array = p_realloc;
            p_sys->index.i_alloc += WEBVTT_PREALLOC * 2;
        }
    }
    if( p_sys->index.i_alloc > p_sys->index.i_count )
    {
        p_sys->index.p_array[p_sys->index.i_count].active = 1; /* tmp start tag */
        p_sys->index.p_array[p_sys->index.i_count++].time = p_cue->i_start;
        p_sys->index.p_array[p_sys->index.i_count].active = 0;
        p_sys->index.p_array[p_sys->index.i_count++].time = p_cue->i_stop;
    }
}