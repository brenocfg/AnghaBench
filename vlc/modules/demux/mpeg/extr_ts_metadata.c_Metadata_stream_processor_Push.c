#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int uint8_t ;
struct TYPE_15__ {scalar_t__ priv; } ;
typedef  TYPE_4__ ts_stream_processor_t ;
struct TYPE_12__ {scalar_t__ i_format; } ;
struct TYPE_16__ {TYPE_2__* p_program; TYPE_1__ metadata; } ;
typedef  TYPE_5__ ts_es_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_6__ block_t ;
struct TYPE_18__ {int /*<<< orphan*/  out; TYPE_3__* p_stream; } ;
struct TYPE_14__ {TYPE_5__* p_es; } ;
struct TYPE_13__ {int /*<<< orphan*/  i_number; } ;
typedef  TYPE_7__ Metadata_stream_processor_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_SET_GROUP_META ; 
 int /*<<< orphan*/  ID3TAG_Parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3TAG_Parse_Handler ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  block_Release (TYPE_6__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_meta_New () ; 

__attribute__((used)) static block_t * Metadata_stream_processor_Push( ts_stream_processor_t *h, uint8_t i_stream_id, block_t *p_block )
{
    Metadata_stream_processor_context_t *ctx = (Metadata_stream_processor_context_t *) h->priv;
    ts_es_t *p_es = ctx->p_stream->p_es;

    if( i_stream_id != 0xbd )
    {
        block_Release( p_block );
        return NULL;
    }

    if( p_es->metadata.i_format == VLC_FOURCC('I', 'D', '3', ' ') )
    {
        vlc_meta_t *p_meta = vlc_meta_New();
        if( p_meta )
        {
            (void) ID3TAG_Parse( p_block->p_buffer, p_block->i_buffer, ID3TAG_Parse_Handler, p_meta );
            es_out_Control( ctx->out, ES_OUT_SET_GROUP_META, p_es->p_program->i_number, p_meta );
            vlc_meta_Delete( p_meta );
        }
    }

    return p_block;
}