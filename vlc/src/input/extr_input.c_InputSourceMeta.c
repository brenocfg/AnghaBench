#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int vlc_meta_t ;
typedef  int /*<<< orphan*/  module_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_10__ {int /*<<< orphan*/ * p_demux; } ;
typedef  TYPE_2__ input_source_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_11__ {scalar_t__ i_attachments; int /*<<< orphan*/  attachments; scalar_t__ p_meta; TYPE_1__* p_item; } ;
typedef  TYPE_3__ demux_meta_t ;
struct TYPE_12__ {TYPE_1__* p_item; int /*<<< orphan*/  attachment_demux; int /*<<< orphan*/  attachment; int /*<<< orphan*/  i_attachment; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AppendAttachment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEMUX_GET_META ; 
 int /*<<< orphan*/  DEMUX_HAS_UNSUPPORTED_META ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 TYPE_7__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * module_need (TYPE_3__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_unneed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_3__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_meta_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_meta_Merge (int*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_3__*) ; 

__attribute__((used)) static void InputSourceMeta( input_thread_t *p_input,
                             input_source_t *p_source, vlc_meta_t *p_meta )
{
    demux_t *p_demux = p_source->p_demux;

    /* XXX Remember that checking against p_item->p_meta->i_status & ITEM_PREPARSED
     * is a bad idea */

    bool has_meta = false;

    /* Read demux meta */
    if( !demux_Control( p_demux, DEMUX_GET_META, p_meta ) )
        has_meta = true;

    bool has_unsupported;
    if( demux_Control( p_demux, DEMUX_HAS_UNSUPPORTED_META, &has_unsupported ) )
        has_unsupported = true;

    /* If the demux report unsupported meta data, or if we don't have meta data
     * try an external "meta reader" */
    if( has_meta && !has_unsupported )
        return;

    demux_meta_t *p_demux_meta =
        vlc_custom_create( p_input, sizeof( *p_demux_meta ), "demux meta" );
    if( unlikely(p_demux_meta == NULL) )
        return;
    p_demux_meta->p_item = input_priv(p_input)->p_item;

    module_t *p_id3 = module_need( p_demux_meta, "meta reader", NULL, false );
    if( p_id3 )
    {
        if( p_demux_meta->p_meta )
        {
            vlc_meta_Merge( p_meta, p_demux_meta->p_meta );
            vlc_meta_Delete( p_demux_meta->p_meta );
        }

        if( p_demux_meta->i_attachments > 0 )
        {
            vlc_mutex_lock( &input_priv(p_input)->p_item->lock );
            AppendAttachment( &input_priv(p_input)->i_attachment, &input_priv(p_input)->attachment, &input_priv(p_input)->attachment_demux,
                              p_demux_meta->i_attachments, p_demux_meta->attachments, p_demux);
            vlc_mutex_unlock( &input_priv(p_input)->p_item->lock );
        }
        module_unneed( p_demux, p_id3 );
    }
    vlc_object_delete(p_demux_meta);
}