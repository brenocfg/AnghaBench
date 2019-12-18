#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  p_next; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_stream_t ;
struct TYPE_13__ {void* psz_lang; } ;
struct TYPE_15__ {TYPE_1__ aenc_cfg; } ;
typedef  TYPE_3__ sout_stream_sys_t ;
struct TYPE_16__ {scalar_t__ i_id; scalar_t__ i_group; void* psz_language; int /*<<< orphan*/  i_codec; int /*<<< orphan*/  i_cat; } ;
typedef  TYPE_4__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Clean (TYPE_4__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_4__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sout_StreamIdAdd (int /*<<< orphan*/ ,TYPE_4__*) ; 
 void* strdup (void*) ; 

__attribute__((used)) static void *transcode_downstream_Add( sout_stream_t *p_stream,
                                       const es_format_t *fmt_orig,
                                       const es_format_t *fmt)
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;

    es_format_t tmp;
    es_format_Init( &tmp, fmt->i_cat, fmt->i_codec );
    es_format_Copy( &tmp, fmt );

    if( !fmt->psz_language )
    {
        if( p_sys->aenc_cfg.psz_lang )
            tmp.psz_language = strdup( p_sys->aenc_cfg.psz_lang );
        else if( fmt_orig->psz_language )
            tmp.psz_language = strdup( fmt_orig->psz_language );
    }

    if( tmp.i_id != fmt_orig->i_id )
        tmp.i_id = fmt_orig->i_id;
    if( tmp.i_group != fmt_orig->i_group )
        tmp.i_group = fmt_orig->i_group;

    void *downstream = sout_StreamIdAdd( p_stream->p_next, &tmp );
    es_format_Clean( &tmp );
    return downstream;
}